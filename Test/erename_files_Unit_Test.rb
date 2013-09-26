require 'FileUtils'

`rm -rf test-tmp-*`






FileUtils.touch "test-tmp-abcabc.txt"
FileUtils.touch "test-tmp-abcdef.txt"
FileUtils.touch "test-tmp-あいうえお.txt"
FileUtils.touch "test-tmp-あああああ.txt"
FileUtils.touch "test-tmp-abc123abc456x.txt"

Dir.mkdir "test-tmp-abc"
Dir.mkdir "test-tmp-d1"

Dir.chdir "test-tmp-d1"
FileUtils.touch "test-tmp-abcabc.txt"
Dir.chdir ".."


puts `ruby erename_files.rb abc ABC * test-tmp-d1/*`

if FileTest.exists? "test-tmp-ABCABC.txt" then
	puts "Test 0001-01: OK"
else
	puts "Test 0001-01: NG"
end

if FileTest.exists? "test-tmp-ABCdef.txt" then
	puts "Test 0001-02: OK"
else
	puts "Test 0001-02: NG"
end


if FileTest.exists? "test-tmp-ABC123ABC456x.txt" then
	puts "Test 0001-03: OK"
else
	puts "Test 0001-03: NG"
end



if FileTest.exists? "test-tmp-abc" then
	puts "Test 0001-04: OK"
else
	puts "Test 0001-04: NG"
end


if FileTest.exists? "test-tmp-d1/test-tmp-ABCABC.txt" then
	puts "Test 0001-05: OK"
else
	puts "Test 0001-05: NG"
end


s = 'ruby erename_files.rb "あ{3}" a * '.encode("Shift_JIS")
puts `#{s}`


if FileTest.exists? "test-tmp-aああ.txt" then
	puts "Test 0002-01: OK"
else
	puts "Test 0002-01: NG or NOT Windows"
end




s = 'ruby erename_files.rb "あ" "b" "test-tmp-あいうえお.txt"'.encode("Shift_JIS")
puts `#{s}`


if FileTest.exists? "test-tmp-aああ.txt" then
	puts "Test 0003-01: OK"
else
	puts "Test 0003-01: NG or NOT Windows"
end


if FileTest.exists? "test-tmp-bいうえお.txt" then
	puts "Test 0003-02: OK"
else
	puts "Test 0003-02: NG or NOT Windows"
end



FileUtils.touch "test-tmp-abb.txt"

puts `ruby erename_files.rb "ab" "aa" * *`

if FileTest.exists? "test-tmp-aab.txt" then
	puts "Test 0004-01: OK"
else
	puts "Test 0004-01: NG"
end





puts `ruby erename_files.rb d1 d2 test-tmp-d1`





