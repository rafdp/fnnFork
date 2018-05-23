set terminal png
set output "graph.png"

set ylabel "BTC USDT"
set xlabel "day"
plot "rnn_output.txt" u 1:2 notitle with lines, "rnn_output.txt" u 1:3 notitle with lines
