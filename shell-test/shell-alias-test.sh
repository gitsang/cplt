

echo  "如果alias是在~/.bash_rc等文件中定义，需要先执行 source ~/.bash_rc"
source /root/.bashrc

echo "检查默认情况下shell脚本中是否开启alias扩展"
shopt expand_aliases   

echo "默认情况下执行定义的alias"
aliasTest

echo "shell中开启alias扩展"
shopt -s  expand_aliases  

echo "shell中开启alias扩展之后检查"
shopt expand_aliases   

echo "shell中开启alias扩展之后，使用alias别名"
aliasTest
