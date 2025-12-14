
$PWD
$EMPTY
$EMPTY echo hi
./test_files/invalid_permission
./missing.out
missing.out
"aaa"
test_files
./test_files
/test_files
minishell.h
$
$?
README.md
ls
ls -l
ls -l -a
echo &
echo \'
echo \"
echo \'\'
echo \"\"
echo \"\'\"
echo \'\"\'
echo \'&\'
ls | cat
ls -l | cat -e
ls -l | grep a | cat -e
echo 1 && echo 2
echo 1 && echo 2 && echo 3
ls -l | cat -e && echo deu bom
ls -l | cat -e && echo deu bom && echo eh isso
ls -l | cat -e && echo deu bom || echo deu ruim agora
ls -l | cat -e || echo deu ruim
< infile
< infile > ./outfiles/outfile
< infile cat > ./outfiles/outfile -e
/bin/cat < todo > ./outfiles/out > ./outfiles/out1 > ./outfiles/out2 < todo
< infile cat > outfile -e && ls < infile > -a outfile -l
< infile cat | grep a > out
> ./outfiles/out | /bin/ls
/bin/ls | < infile
/bin/ls | /bin/grep o > ./outfiles/out | /bin/ps
/bin/ps > ./outfiles/out | /bin/ls | /bin/grep o
< infile cat > outfile | < infile grep a
()
(ls)
(ls -l)
((ls -l))
((ls -l))
(ls) -l
(ls) -l -a
-l (ls)
< infile (/bin/cat > ./outfiles/out -e > ./outfiles/out2 | /bin/ps)
( /bin/ls < infile ) < infile | < infile /bin/cat -e && ( ( ( < infile /bin/cat -e ) ) )
< todo ( < todo /bin/ls < infile ) < infile | < infile /bin/cat -e && < infile ( < infile ( < infile ( < infile /bin/cat -e < todo ) < todo ) < todo ) < todo
(<infile())
<infile())
((/bin/ls)
(/bin/ls))
echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e && < infile2 cat
echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e && < infile2 cat
< infile1 cat
echo hi
echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e
dsfasdf || echo hello | cat -e && echo bye || echo kitty
echo oi && ech oi2 | echo oi3 | echo oi4 || echo oi5
ech oi && echo hi | echo hello | echo bonjour || echo haha
echo oi || echo hi && echo hello && echo bonjour || echo haha
ech && echo oi || echo hey
ech oi || echo oi && echo hi | cat -e
echo hello | cat -e && ls | wc -l
echo hi > ./outfiles/infile1 && echo bye > ./outfiles/infile2
echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e && < infile2 cat
< infile1 cat
< infile1 cat | echo
echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e
cat ./outfiles/outfile1
cat > .
cat > ./outfiles/
cat > usr/local/bin
cat > /usr/local/bin
cat > ./outfiles/\"\"
cat > ./outfiles/\'\'
echo bye > ./outfiles/\" \"
cat < ./outfiles/\" \"
echo hi > ./outfiles/\' \'
cat < ./outfiles/\' \'
echo hello > ./outfiles/\"fdasdfsa\"
cat < ./outfiles/\"fdasdfsa\"
echo kitty > ./outfiles/\"\"fdasdfsa\"\"
cat < ./outfiles/\"\"fdasdfsa\"\"
cat < ./outfiles/.
cat < ./outfiles//
cat < usr/local/bin
cat < /usr/local/bin
cat < ./outfiles/\"\"
cat < ./outfiles/\'\'
cat < ./outfiles/\" \"
cat < ./outfiles/\' \'
cat < ./outfiles/\"fdasdfsa\"
cat < ./outfiles/\"\"fdasdfsa\"\"
echo hi > ./outfiles/.
echo hi > ./outfiles//
echo hi > usr/local/bin
echo hi > /usr/local/bin
echo hi > ./outfiles/\"\"
echo hi > ./outfiles/\'\'
echo hi > ./outfiles/\" \"
cat < ./outfiles/\" \"
echo bye > ./outfiles/\' \'
cat < ./outfiles/\' \'
echo hi < ./outfiles/.
echo hi < ./outfiles//
echo hi < usr/local/bin
echo hi < /usr/local/bin
echo hi < ./outfiles/\"\"
echo hi < ./outfiles/\'\'
echo hi < ./outfiles/\" \"
echo hi < ./outfiles/\' \'
export var=usr/local/bin var01=filename && cat > ./outfiles/$var
export var01=filename && cat infile1 > ./outfiles/\"\"$var01\"\"
export var01=filename && cat ./outfiles/\"\"$var01\"\"
cat > ./outfiles/\"\"$vor\"\"
cat > ./outfiles/$vor
echo $\"\" USER
echo $\"\" USER \"\"
echo $\"\"\"                 \" USER \"\" hi
echo $\"\"\"\"\"\"\"\"\"\"\"\" USER \"\" hey
echo $\"\"\"\" USER \"\" a
echo $\"\"\'\' USER \"\" b
echo $\'\' USER \"\"c
echo $\'\'\'\' USER \"\"d
echo $\' \' \'\' USER \"\" e
echo $\' \'\"\" USER \"\" f
echo $\"\'\'\" USER \"\"g
echo $\'\'\'\' USER \"\" h
echo $  \"\'\'\" USER \"\" i
echo $  \"\"\"\" USER \"\" j
echo $  \"\" USER
echo \"        $USER   \" k
echo $
echo $$
echo $$$
$
$$
$$$
export carol=55 && echo $carol
export carol=55 && echo \"carol\"
export carol=55 && echo $\"carol\"
export carol=55 && echo \"$carol\"
export carol=55 && echo \'$carol\'
export carol=55 && echo $carolbia$
export carol=55 && echo $carolbia$ hi
export carol=55 && echo $carol$?bia$ hi
export carol=55 && $\'carol\'$\'bia\'$
export carol=55 && echo $\"carol\"$\"bia\"$
export carol=55 && $\'carol\'\'bia\'
export carol=55 && $\"carol\"\"bia\"
export carol=55 && echo $carolbia$ | cat -e > outfile3 && echo bye
export carol=55 var=\"o hello\" var50=\"abc      def\" && ech$var
export carol=55 var=\"o hello\" var50=\"abc      def\" && echo $var50
echo $adfasfsd
$adfasfsd
$%342342
$\"342342
export \"\"
export var30 && export | grep var30
export var30 && export var30=carol && export | grep var30
export var20=bia && export | grep var20
export var20=bia && export var20 && export | grep var20
export var=variable && export $var=carol && export | grep $var
export var40=oi var50=hi && export var= && export | grep var=\"\"
export var= && export var=20 && export | grep var=
export var=20 && export var= && export | grep var=
export var70 && export | grep var70
export var10 && export var100 && export | grep var10
export \" \"
export \'\'
export \' \'
export var=variable && export $var=$USER && export | grep variable=
export var=oi | echo hey
unset \"\"
export var=variable && export $var=123
export var20=carol && export | grep var20
export var30 && export | grep var30
export var40= && export | grep var40
export carol=55 && $USER$carol
export carol=55 && export var=variable && $USER$var
oitudobem
$USERoi
$USER\'
\"$USER\"
\'$USER\'
\"$USER\'
$
$$
$$$
echo oi > ./outfiles/tudo bem
cat ./outfiles/tudo
< infile1 cat | echo hey
echo hey | < infile1 cat
whoami | < infile1 cat
rm infile1
echo hey | < infile1 cat
whoami | < infile1 cat
echo hi | (echo hello | cat -e)
echo hi | (echo hello && echo bye) | cat -e
(export var=carol) && export | grep var=
(ech hi || echo carol > ./outfiles/outfile1 && echo bia) | cat -e && echo bye
(ech hi || (echo carol > ./outfiles/outfile1 && echo bia)) | cat -e && echo bye
(ech hi || (echo carol > ./outfiles/outfile1  | echo bia)) | cat -e && echo bye
(echo bye) echo hi ) (ls (echo hi)
(echo bye)) ((echo hi)
((echo hi | cat -e) | cat -e)
echo \"(hello)\" > ./outfiles/infile1
cat ./outfiles/infile1 | grep \");\"$
cat ./outfiles/infile1 | grep \"(\"
(a$$'"')
""
''
(a)
echo − -$$
..
     
	 