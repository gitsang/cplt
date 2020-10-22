
g++ t_virtual.cpp -o t_virtual

g++ t_virtual2.cpp -o t_virtual2
g++ -S -fverbose-asm -g t_virtual2.cpp -o t_virtual2.s
as -alhnd t_virtual2.s > t_virtual2.as
