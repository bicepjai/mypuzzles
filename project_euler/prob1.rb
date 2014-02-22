# rfile = File.new("A-small-practice.in", "r")
# rfile = File.new("A-large-practice.in", "r")
# rfile = File.new("in.in", "r")
# wfile = File.new("output.out", "w")
# 
# cases = rfile.gets.to_i
# puts cases
# (0..cases-1).each do |c1|
#   x,s,r,t,n = rfile.gets.gsub(/\n/,"").split(" ").collect { |str| str.to_i }
#   wfile.print "Case ##{c1+1}: "
#   (0..rows-1).each do |row|
#       rfile.gets.gsub(/\n/,"").split(" ").collect { |str| str.to_i }
#   end
# end
# 
# rfile.close
# wfile.close

sum = 0
(1..999).each do |n|
  if n%3 == 0 || n%5 == 0
    sum += n
  end
end

puts sum