# rfile = File.new("A-small-practice.in", "r")
rfile = File.new("A-large-practice.in", "r")
wfile = File.new("output.out", "w")

cases = rfile.gets.to_i
# puts cases
(0..cases-1).each do |c1|
  rows,cols = rfile.gets.gsub(/\n/,"").split(" ").collect { |str| str.to_i }
  wfile.puts "Case ##{c1+1}:"
  data = []
  count_init = 0
  (0..rows-1).each do |row|
      data[row] = rfile.gets.gsub(/\n/,"")
      data[row].each_byte {|ch| if ch == 35 then count_init+=1 end}
  end
  
  flag = false
  if count_init%4 == 0
    (0..rows-1).each do |row|
      (0..cols-1).each do |col|
        if row+1 < rows and col+1 < cols and data[row][col] != '.' and data[row][col] == '#'
          if data[row+1][col] == '#' && data[row][col+1] == '#' && data[row+1][col+1] == '#'
            data[row][col]      = '/'
            data[row+1][col]    = '\\'
            data[row][col+1]    = '\\'
            data[row+1][col+1]  = '/'
          end
        end
      end
      data[row].each_byte {|ch| if ch == 35 then flag = true end}
      if flag
        if cases-1 == c1
          wfile.print "Impossible"
        else
          wfile.puts "Impossible"
        end
        break       
      else
        if cases-1 == c1 and row == rows-1
          wfile.print "#{data[row]}"
        else
          wfile.puts "#{data[row]}"
        end
      end
    end
  else
    if cases-1 == c1
      wfile.print "Impossible"
    else
      wfile.puts "Impossible"
    end
  end
end

rfile.close
wfile.close