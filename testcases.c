(echo start && (sleep 2 && echo mid) && echo end) | cat

((echo "start" && (ls -l /usr || (whoami && pwd))) || (("id -u" && date) || uname -r)) | (cat /etc/passwd | grep "root" | wc -l) && ((df -h && (echo 'disk usage' || du -sh /home)) || (ps aux | grep "bash" && (uptime || echo "no uptime")))

echo start | sleep 2 | echo mid | echo end | cat

< /dev/sdtout ls | ls > /dev/sdout

ls && (ls&& ls -l  ) | cat -n

(echo Start && ((ls | wc -l) || echo Fail)) || ((pwd && echo Mid) && (whoami || echo End))

(echo 1 && (echo 2 || (echo 3 && (echo 4 || (echo 5 && echo 6))))) && echo Done

(ls && (echo A || (echo B && echo C))) || ((echo D && echo E) && (echo F || echo G)) && (echo H || (echo I && (echo J || echo K)))

ls |  sleep 2 && ls

$123ammie

$a"bin"$a"ls"

$
$: command not found

==1881473==    at 0x407C21: ft_atoi (in /home/aelsayed/Desktop/minishell/minishell)
==1881473==    by 0x401696: ft_shlvl (main.c:97)
==1881473==    by 0x401791: main (main.c:120)
==1881473== 

some test cases:

minishell$ echo "$""HOME"
echo $HOME
$HOME
minishell$ bash
bash
aelsayed@c3r9p8:~/Desktop/minishell$ echo "$""HOME"
$HOME
aelsayed@c3r9p8:~/Desktop/minishell$ echo $""HOME
HOME
minishell$ echo $""HOME
echo $HOME
$HOME

export A="hello" B='world' C='"quoted $A"' D="'literal $B'" && echo "$A $B" && echo $C && echo $D && unset A || echo fallback && export E=test && (echo "$E" && export F="$E 42" && echo "$F" && unset E F) && echo done || echo failed

ls *"*"
ls Makefile README.md built-ins execution garbage.c libft main.c minishell.h parsing testcases.c minishell * ****
ls: cannot access '**': No such file or directory

we should test if anyfile has "quotes" how it would work with us even mahndlia like touch '"' and ls *'"' shoould show us the file

ls>(asd) :: syntax error

minishell$ ls>*
Command not found : ls>ls>*

$* should be handled !!

close the fd 1 with close(1) in terminal