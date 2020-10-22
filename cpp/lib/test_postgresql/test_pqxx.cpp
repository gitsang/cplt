#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
    char* sql;
    
    try{
        connection C("dbname=yfuse user=postgres hostaddr=127.0.0.1 port=5432");
        if(C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }else {
            cout << "Can't open database" << endl;
            return 1;
        }
        /* Create SQL statement */
        sql = (char*) \
              "create table file_info (" \
              "    inode        integer         primary key," \
              "    file_mode    integer         default 0100777," \
              "    file_owner   varchar(255)    not null," \
              "    file_group   varchar(255)    not null," \
              "    file_size    integer         default 0," \
              "    mtime        timestamp       default 'now'," \
              "    ctime        timestamp       default 'now'," \
              "    file_name    varchar(255)    not null," \
              "    father_path  varchar(255)    not null" \
              ");";

        /* Create a transactional object. */
        work W(C);
        
        /* Execute SQL query */
        W.exec( sql );
        W.commit();
        cout << "Table created successfully" << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}  
