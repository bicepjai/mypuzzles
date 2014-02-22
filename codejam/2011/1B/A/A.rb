rfile = File.new("in.in", "r")
wfile = File.new("output.out", "w")

cases = rfile.gets.to_i
# puts cases
(0..cases-1).each do |c1|
  N = rfile.gets.to_i
  puts "==>#{N}"
  data = []
  wp = []
  (0..N-1).each do |n1|
    data[n1] = rfile.gets.gsub(/\n/,"")
    zeros = ones = dots = 0
    data[n1].split(//).each {|ch| (ch=='1') ? ones+=1 : (ch=='0') ? zeros+=1 : dots+=1}
    wp[n1] = ones.to_f / (ones + zeros).to_f
    puts "#{n1} =>#{data[n1]}<= #{ones} #{zeros} #{dots} wp:#{wp[n1]}" 
  end

  owp = []
  (0..N-1).each do |n1|
    owp1 = zeros = ones = dots = 0
    data[n1].split(//).each_with_index do |ch,i| 
      if ch=='1'
        owp1+=wp[i]
        ones+=1
      elsif ch=='0'
        owp1+=wp[i]
        zeros+=1
      else
        owp1+=0
        dots+=1
      end
    end
    puts "owp1: #{owp1}"
    owp[n1] = owp1.to_f / (ones + zeros).to_f
    puts "owp:#{owp[n1]}"
  end

  oowp = []
  (0..N-1).each do |n1|
    oowp1 = zeros = ones = dots = 0
    data[n1].split(//).each_with_index do |ch,i| 
      if ch=='1'
        oowp1+=wp[i]
        ones+=1
      elsif ch=='0'
        oowp1+=wp[i]
        zeros+=1
      else
        oowp1+=0
        dots+=1
      end

    end
    oowp[n1] = oowp1.to_f / N.to_f
    puts "oowp:#{oowp[n1]}"
  end
  
  rpi = 0
  (0..N-1).each do |n1|
    rpi = 0.25 * wp[n1] + 0.50 * owp[n1] + 0.25 * oowp[n1]
  end
  puts "rpi:#{rpi}"
  puts "======"
end

rfile.close
wfile.close