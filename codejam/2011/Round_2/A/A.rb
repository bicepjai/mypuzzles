rfile = File.new("A-small-practice.in", "r")
# rfile = File.new("A-large-practice.in", "r")
# rfile = File.new("in.in", "r")
wfile = File.new("output.out", "w")

cases = rfile.gets.to_i
# puts cases
(0..cases-1).each do |c1|
  x,s,r,t,n = rfile.gets.gsub(/\n/,"").split(" ").collect { |str| str.to_i }
  # puts "==>#{x}"
  # wfile.puts "Case ##{c1+1}:"
  wfile.print "Case ##{c1+1}: "
  rows = n;  walkway_data = []; eb_len = 0
  time_taken = 0
  time_left = t
  (0..rows-1).each do |row|
      b,e,w = rfile.gets.gsub(/\n/,"").split(" ").collect { |str| str.to_i }
      walkway_data[row] = [e-b,w]
      eb_len += e-b
      # puts "#{b},#{e},#{w}"
  end
  dist = x-eb_len
  # puts "walking #{dist} @ #{s}"
  est_t = dist.to_f/r.to_f
  if est_t > time_left
    rem_dis = dist.to_f - (r.to_f * time_left.to_f)
    time_taken = time_taken.to_f + time_left.to_f + (rem_dis.to_f/s.to_f)
    if time_left > 0 then time_left = time_left.to_f - (rem_dis.to_f/s.to_f) end
  else
    time_taken = time_taken.to_f + est_t.to_f
    time_left = time_left.to_f - est_t.to_f   
  end
  # puts "time_left #{time_left}"
  # puts "time_taken #{time_taken}"
  walkway_data_s = walkway_data.sort_by!{|v| v[1]}
  walkway_data_s.each do|walkway|
    # puts "walkwaying #{walkway}"
    wdist = walkway[0]
    ws = walkway[1]
    west_t = wdist.to_f/(ws+r).to_f
    if west_t > time_left
      wrem_dis = wdist.to_f - ((ws+r).to_f * time_left.to_f)
      time_taken = time_taken.to_f + time_left.to_f + (wrem_dis/(ws+s)).to_f
      if time_left > 0 then time_left = time_left.to_f - (wrem_dis.to_f/(ws+s).to_f) end      
    else
      time_taken = time_taken + west_t
      time_left = time_left - west_t  
    end
    # puts "time_left #{time_left}"
    # puts "time_taken #{time_taken}"    
  end
  if c1 == cases-1
    wfile.print time_taken
  else
    wfile.puts time_taken
  end
end

rfile.close
wfile.close