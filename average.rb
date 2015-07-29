file_input = ARGV[0] || "sample.txt"

all_commands = Array.new
File.open(file_input, "r").each_line do |line|
  next if line.empty?

  command = line.split(" ").map{|x| x.strip.sub("m", "").sub("s", "").to_i}.compact
  print("Detected commands #{command.size}\n")

  all_commands.push(command)
end

avearge = Array.new

i = 0
print("Size: #{all_commands[0].size}")
while i < all_commands[0].size  do

  j = 0
  command = all_commands[i]

  if command.nil?
    i += 1
    next
  end
  next if command.nil?
  while j < command.size do
    
    avearge[j] = 0 if avearge[j].nil?
    avearge[j] += command[j]
    j += 1
  end
  i +=1
end

avearge = avearge.map{|x| x/all_commands.size}

print("Results: #{avearge} !!")

