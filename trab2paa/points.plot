reset
unset key
unset tics 
unset border 
set pointsize 0.1
set term pdf enhanced 
set out 'pontos.pdf'
plot 'input2.txt' with points pt 7
