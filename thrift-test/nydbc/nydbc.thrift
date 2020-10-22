namespace java com.yealink.dbc.idl
namespace cpp com.yealink.dbc.idl
namespace go com.yealink.dbc.idl
 
enum db_exception_code {
    E_NONE                           = 0,      //none
    E_EXCEPT_START                   = 710000, //起始code
    E_NONINTERACT_BATCH_OVER_LIMITED = 710001, //noninteract batch over limited
    E_INTERACT_BATCH_OVER_LIMITED    = 710002, //interact over limited
    E_BATCH_AUTH_FAILED              = 710003, //batch {k t r} invalid
    E_BATCH_NOT_EXIST                = 710004, //batch expired or invalid
    E_SQL_INTERNAL_ERROR             = 710005, //sql error
    E_REDIS_INTERNAL_ERROR           = 710006, //other redis excluded here
    E_PARAMETER_ERROR                = 710007, //interface param input error
    E_REDIS_KEY_OR_FIELD_NOT_EXIST   = 710008, //get/hget->nil
    E_REDIS_LOCK_OWNER_NO_MATCH      = 710009, //uplock/unlock check owner no match
    E_REDIS_LOCK_RESOURCE_IN_USE     = 710010  //lock resource in use
}
 
/*
 * nydbc接口异常码，详细信息
 */
exception db_exception{
    1:i32 code;   //see enum db_exception_code;
    2:string str; //detail of code
}
 
/*
 * sql事务标识包括k,t,r
 */
struct sql_batch{
    1:string k;
    2:i64 t;
    3:string r;
}
 
/*
 * sql事务隔离级别(当前默认是TIL_RC)
 */
enum transaction_isolation_level{
    TIL_RU = 0,
    TIL_RC = 1,
    TIL_RR = 2,
    TIL_SI = 3,
    TIL_SSI = 4
}
 
/*
 * sql事务类型标识：交互式式与非交互式
 */
struct sql_batch_filter{
    1:optional bool interact; // no-set(default:noninteractive), true(interactive), false(noninteractive)
    2:optional transaction_isolation_level til; //TIL_RC default
}
 
/*
 * 申请分布式锁信息，对keys做原子性操作
 */
struct db_lock{
    1:list<string> keys;              //资源信息，不能为空，默认[1,200]个
    2:string owner;                   //拥有者 不能为空
    3:optional i64 hold_time_mseconds;//-1(default), (0, MAX]; MAX 和-1的保持时长是 (INT64_MAX - now_timestamps)ms
    4:optional i64 try_time_mseconds; //-1(default), [0, MAX]; 0立刻返回，除非服务端有限制, 否则MAX和-1的重试最长时间是(INT64_MAX - now_timestamps)ms
    5:optional string remark;         //备注信息
}
 
/*
 * sql查询携带的参数
 */
struct sql_query_filter{
    1:string sql;
    2:optional sql_batch batch;
}
 
/*
 * sql更新
 */
struct sql_update_filter{
    1:string sql;
    2:optional sql_batch batch;
}
 
/*
 * the return values of update return *;
 */
struct sql_update_return{
    1: list<string> cols;                //column names, list的size大小与rows里每个内部list一样
    2: optional list<list<binary>> rows; //rows; binary 与sql_query返回的binary定义一样，首字节类型，后面字节为具体数据
}
 
/*
 * 要删除的key列表
 */
struct redis_del_filter{
    1:list<string> keys;
}
 
/*
 * 类似redis::string::set
 */
struct redis_set_filter{
    1:string key;
    2:binary value;
    3:optional i64 hold_time_mseconds; //-1(default), (0, MAX]; MAX 和-1的保持时长是 (INT64_MAX - now_timestamps)ms
    4:optional bool set_if_not_exist;  //no-set(default, overwrite old key), true(NX), false(XX)
}
 
/*
 * 自扩展数据类型hashex，此hmsetex的参数
 */
struct redis_hmsetex_filter {
    1:string field;
    2:binary value;
    3:i64 hold_time_mseconds; //-1(default), (0, MAX]; MAX 和-1的保持时长是 (INT64_MAX - now_timestamps)ms
}
 
/*
 * region信息
 */
struct region {
    1:string country;
    2:string area;
    3:string master_id;
    4:string slave_id;
}
 
/*
 * region增量查询
 */
struct region_filter{
    1:i64 version;
}
 
/*
 * region信息
 */
struct region_out{
    1:region reg;
    2:i64 version;
}
 
service nydbc{
    //ping
    /*
     * reply with true at normal
     */
    bool ping()
        throws (1:db_exception dberr);
    // batch
    /*
     * descript: sql事务的begin,申请一个事务标识
     * param: filter 要申请的事务类型
     * return: 事务标识，当k或r为空时, 申请失败
     * exception: 包括thrift异常和nydbc自定义的异常
     */
    sql_batch start(1:sql_batch_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: sql事务提交，batch由start()生成
     * param: batch 由start()生成
     * return: 交互式在sql commit成功才成功，
     *         非交互式，无sql_update语句返回失败，
     * exception: 校验batch失败抛710003,
     *            交互式/非交互式过期时抛710004,
     *            非交互式无sql_update语句时也抛710004
     */
    bool commit(1:sql_batch batch)
        throws (1:db_exception dberr);
 
    /*
     * descript: 回滚事务
     * param: batch 由start()生成
     * return: 校验失败返回false, 其他默认都为true
     * exception: 校验batch失败抛710003,
     */
    bool rollback(1:sql_batch batch)
        throws (1:db_exception dberr);
 
    /*
     * descript: 根据资源(db_lock.keys)获取分布式锁
     * param:  lock 如上db_lock
     * return: 返回锁id, 非空串为正常，其他为异常
     * exception: 传参错误(包括keys个数>200,key为空串)抛710007
     *            资源被使用抛710010,redis异常抛710006
     */
    string lock(1:db_lock lock)
        throws (1:db_exception dberr);
 
    /*
     * descript: 释放分布式锁
     * param: lock lock()申请的id
     *        owener lock()申请时的owner
     * return: 释放成功true
     * exception: redis异常抛710006, owner校验不通过抛710009
     */
    bool unlock(1:string lock, 2:string owner)
        throws (1:db_exception dberr);
 
    /*
     * descript: 续期/更新 lock
     * param:lock lock()申请的id
     *       owner lock()申请时的owner
     *       hold_time_mseconds(ms):-1 (default, keep (INT64_MAX-ms_now)),
     *                              (0, INT64_MAX-ms_now] ok,
     *                              other error
     * return: 成功true，其他看异常
     * exception: redis异常抛710006, owner校验不通过抛710009
     */
    bool uplock(1:string lock, 2:string owner, 3:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    // sql
    /*
     * descript: sql select语句，返回list<map<>>，请自行保证col_name的唯一性
     *           多语句时，必须都是select，默认返回最后一条select语句的结果
     * param: filter 如sql_query_filter
     * return: list<map<>>，colname 需保证唯一性
     * exception: 参数错误（非select语句，语法错误）抛710007
     *            batch校验失败抛 710003
     *            sql语句不存在/过期抛 710004
     *            sql执行逻辑错误抛 710005
     */
    list<map<string, binary>> sql_query(1:sql_query_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: sql update/insert/delete 语句调用接口
     *           多语句时，默认返回最后一条update/insert/delete语句的返回值
     * param: filter 如sql_update_filter
     * return: sql 执行的返回值
     * exception: 参数错误（非select语句，语法错误）抛710007
     *            batch校验失败抛 710003
     *            sql语句不存在/过期抛 710004
     *            sql执行逻辑错误抛 710005
     */
    i64 sql_update(1:sql_update_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: sql update/insert/delete 语句调用接口
     *           默认不支持多语句
     * param: filter 如sql_update_filter
     * return: sql 执行的返回值
     * exception: 参数错误（非select语句，语法错误）抛710007
     *            batch校验失败抛 710003
     *            sql语句不存在/过期抛 710004
     *            sql执行逻辑错误抛 710005
     */
    sql_update_return sql_update_with_return(1:sql_update_filter filter)
        throws (1:db_exception dberr);
 
    // redis
    /*
     * descript: 为key设置过期时间
     * param: key redis-key, hold_time_mseconds milliseconds
     * return: 成功为true，其他false
     * exception: redis错误抛710006
     */
    bool redis_pexpire(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量删除key
     * param: filter如redis_del_filter
     * return: 被删除的key个数
     * exception: redis错误抛710006
     *            参数错误（list.size() > 200 || <= 0），抛710007
     */
    i64 redis_del(1:redis_del_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 为key存储的value 加上step
     * param: key string-key, step INT64_MIN~INT64_MAX
     * return: 新的key-value
     * exception: redis错误抛710006
     */
    i64 redis_incrby(1:string key, 2:i64 step)
        throws (1:db_exception dberr);
 
    /*
     * descript: 类redis set
     * param: filter 如上redis_set_filter
     * return: 设置成功返回true，未成功false
     * exception: 参数错误（hold_time_mseconds <= 0），抛710007
     *            redis错误抛710006
     */
    bool redis_set(1:redis_set_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取key的值
     * param: key 字符串类型
     * return: binary 空串亦合理
     * exception: redis错误抛710006
     *            key不存在抛710008
     */
    binary redis_get(1:string key)
        throws (1:db_exception dberr);
 
    /*
     * descript: 类似redis hset，设置hash field的值
     * param: key hash-key, hkey hash-field, value hash-key-field's-value
     * return: bool 增加并设置field成功返回true，非首次设置返回false，失败false
     * exception: redis错误抛710006
     */
    bool redis_hset(1:string key, 2:string hkey, 3:binary value)
        throws (1:db_exception dberr);
 
    /*
     * descript: 类似redis hset，设置hash field的值
     * param: key hash-key, fvs <field, value>的映射
     * return: 设置成功返回true，key非hash-key 返回false
     * exception: redis错误抛710006
     *            参数错误（map.size() > 200 || <= 0），抛710007
     */
    bool redis_hmset(1:string key, 2:map<string, binary> fvs)
        throws (1:db_exception dberr);
 
    /*
     * descript: 删除hash-field
     * param: key hash-key, hkey hash-field
     * return: 成功删除的field个数
     * exception: redis错误抛710006
     */
    i64 redis_hdel(1:string key, 2:string hkey)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量删除hash-field
     * param: key hash-key, hkeys hash-fields
     * return: 成功删除的field个数
     * exception: redis错误抛710006
     *            参数错误（set.size() > 200 || <= 0），抛710007
     */
    i64 redis_hmdel(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hash-field的值
     * param: key hash-key, hkey hash-field
     * return: binary ，key/field不存在抛710008
     * exception: redis错误抛710006
     *            key/field不存在抛710008
     */
    binary redis_hget(1:string key, 2:string hkey)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量获取hash-field的值
     * param: key hash-key, hks hash-fields
     * return: map<field, value> 存在的field的才返回
     * exception: redis错误抛710006
     *            参数错误（set.size() > 200 || <= 0），抛710007
     */
    // return the found <field, value>; throw exception on set.size() > 200
    map<string, binary> redis_hmget(1:string key, 2:set<string> hks)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hash-field个数
     * param: key hash-key
     * return: field个数
     * exception: redis错误抛710006
     */
    i64 redis_hlen(1:string key)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hash-key的field值（其个数不能超过200个）
     * param: key hash-key
     * return: map<field, value>， map.size() > 200 || <= 0 返回空
     * exception: redis错误抛710006
     */
    map<string, binary> redis_hgetall(1:string key)
        throws (1:db_exception dberr);
 
    /*
     * descript: 查找符合给定模式的key
     * param: reg redis支持的正则表达式
     * return: list<key>
     * exception: redis错误抛710006
     */
    list<string> redis_keys(1:string reg)
        throws (1:db_exception dberr);
 
    /*
     * descript: 自定义数据结构hashex，支持field过期，
     *           该函数为hashex-key-field写入值
     * param: key hashex-key, hkey hashex-field, value hashex-field的value,
     *        hold_time_mseconds(milliseconds): 留存时长
     *                      -1 default, keep (INT64_MAX-ms_now)ms,
     *                      (0, INT64_MAX-ms_now] ms ok,
     *                      other error
     * return: 新增并设置成功true，非首次false，其他false
     * exception: redis错误抛710006
     */
    bool redis_hsetex(1:string key, 2:string hkey, 3:binary value, 4:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量写入hash-key的field-value
     * param: key hashex-key, fvts 批量的redis_hmsetex_filter
     * return: 有写入返回true，key非hash-key返回false
     * exception: redis错误抛710006
     *            参数错误（list.size() > 200 || <= 0），抛710007
     */
    bool redis_hmsetex(1:string key, 2:list<redis_hmsetex_filter> fvts)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hash-key的field值
     * param: key hashex-key, hkey hashex-field
     * return: 返回hash-field的值，不存在抛710008
     * exception: redis错误抛710006
     *            key不存在抛710008
     */
    binary redis_hgetex(1:string key, 2:string hkey)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量获取hash-key对应的fields的值
     * param: key hashex-key, hkeys hashex-fields
     * return: map<field, value>
     * exception: redis错误抛710006
     *            参数错误（list.size() > 200 || <= 0），抛710007
     */
    map<string, binary> redis_hmgetex(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 设置hashex-field失效
     * param: key hashex-key, field hashex-field
     *        hold_time_mseconds: milliseconds
     *               -1 default, keep (INT64_MAX-ms_now)ms),
     *               (0, INT64_MAX-ms_now]ms ok,
     *               other error
     * return: 成功true，其他false
     * exception: redis错误抛710006
     */
    bool redis_hexpire(1:string key, 2:string field, 3:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 批量删除hashex-field
     * param: key hashex-key, hkeys hashex-field
     * return: 被删除的field个数
     * exception: redis错误抛710006
     *            参数错误（set.size() > 200 || <= 0），抛710007
     */
    i64 redis_hdelex(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hashex-field个数，可能包含已过期还未及时删除的field
     * param: key hashex-key
     * return: hashex当前field个数
     * exception: redis错误抛710006
     */
    i64 redis_hlenex(1:string key)
        throws (1:db_exception dberr);
 
    /*
     * descript: 获取hashex-key的未过期field值（其个数不能超过200个）
     * param: key hash-key
     * return: map<field, value>，当field-value >200 返回空
     * exception: redis错误抛710006
     */
    // throw exception if key's valid field > 200
    map<string, binary> redis_hgetallex(1:string key)
        throws (1:db_exception dberr);
 
    /*
     * descript: 对hashex的key进行过期
     * param:key hashex-key
     *       hold_time_mseconds: milliseconds
     *                  -1 remove ttl,
     *                  > 0 ok,
     *                  others error
     * return: 成功true，其他失败（如非hashex-key）
     * exception: redis错误抛710006
     */
    bool redis_pexpireex(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /************************************************************/
    /****************************region**************************/
    /*
     * descript: 获取version > filter.version的各region的信息
     * param: filter, 0取所有
     * return: list<region_out>, 返回增量查询的region信息
     * exception:
     */
    list<region_out> get_region(1:region_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 增加/更新region的信息
     * param: regions 一次插入/更新最多200个
     * return: bool 有更新则返回true
     * exception:
     */
    bool put_region(1:list<region> regions)
        throws (1:db_exception dberr);
 
    /************************************************************/
    /**********************redis_global_*************************/
    /*
     * descript: 该接口的数据会全球同步，其他如redis_pexpire
     * param:
     * return:
     * exception:
     */
    bool redis_global_pexpire(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_del
     * param:
     * return:
     * exception:
     */
    i64 redis_global_del(1:redis_del_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_set
     * param:
     * return:
     * exception:
     */
    //redis global like not-global function
    bool redis_global_set(1:redis_set_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hset
     * param:
     * return:
     * exception:
     */
    bool redis_global_hset(1:string key, 2:string hkey, 3:binary value)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hmset
     * param:
     * return:
     * exception:
     */
    bool redis_global_hmset(1:string key, 2:map<string, binary> fvs)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hdel
     * param:
     * return:
     * exception:
     */
    i64 redis_global_hdel(1:string key, 2:string hkey)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hmdel
     * param:
     * return:
     * exception:
     */
    i64 redis_global_hmdel(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hsetex
     * param:
     * return:
     * exception:
     */
    bool redis_global_hsetex(1:string key, 2:string hkey, 3:binary value, 4:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hmsetex
     * param:
     * return:
     * exception:
     */
    bool redis_global_hmsetex(1:string key, 2:list<redis_hmsetex_filter> fvts)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hexpire
     * param:
     * return:
     * exception:
     */
    bool redis_global_hexpire(1:string key, 2:string field, 3:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_hdelex
     * param:
     * return:
     * exception:
     */
    i64 redis_global_hdelex(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会全球同步，其他如redis_pexpireex
     * param:
     * return:
     * exception:
     */
    bool redis_global_pexpireex(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /************************************************************/
    /**********************redis_peer_*************************/
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_pexpire
     * param:
     * return:
     * exception:
     */
    bool redis_peer_pexpire(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_del
     * param:
     * return:
     * exception:
     */
    i64 redis_peer_del(1:redis_del_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_set
     * param:
     * return:
     * exception:
     */
    bool redis_peer_set(1:redis_set_filter filter)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hset
     * param:
     * return:
     * exception:
     */
    bool redis_peer_hset(1:string key, 2:string hkey, 3:binary value)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hmset
     * param:
     * return:
     * exception:
     */
    bool redis_peer_hmset(1:string key, 2:map<string, binary> fvs)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hdel
     * param:
     * return:
     * exception:
     */
    i64 redis_peer_hdel(1:string key, 2:string hkey)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hmdel
     * param:
     * return:
     * exception:
     */
    i64 redis_peer_hmdel(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hsetex
     * param:
     * return:
     * exception:
     */
    bool redis_peer_hsetex(1:string key, 2:string hkey, 3:binary value, 4:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hmsetex
     * param:
     * return:
     * exception:
     */
    bool redis_peer_hmsetex(1:string key, 2:list<redis_hmsetex_filter> fvts)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hexpire
     * param:
     * return:
     * exception:
     */
    bool redis_peer_hexpire(1:string key, 2:string field, 3:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_hdelex
     * param:
     * return:
     * exception:
     */
    i64 redis_peer_hdelex(1:string key, 2:set<string> hkeys)
        throws (1:db_exception dberr);
 
    /*
     * descript: 该接口的数据会region对互相同步，其他如redis_pexpireex
     * param:
     * return:
     * exception:
     */
    bool redis_peer_pexpireex(1:string key, 2:i64 hold_time_mseconds)
        throws (1:db_exception dberr);
}
 
