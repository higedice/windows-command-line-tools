#!/usr/local/bin/ruby
#
#  rename_files.rb
#
#  2013/07/13	new
#		Is it better to get all filenames to rename first and then
#		rename?
#


$PRONGRAM_VERSION = '2.0.0'
$PRONGRAM_DATE = '2013/09/18'



def print_usage
  $stderr.puts <<EOS
Usage: ruby erename_files.rb PATTERN NEW_STRING <files>... 

This program *CANNOT* UNDO!

Search for PATTERN in files and each one's name in target directorys and
replace to NEW_STRING.
PATTERN is an extended regular expression.

Example: ruby rename_files.rb "foto of " "" path/to/* "foto of 2013-07-12.jpg"

 rename_files.rb version #{$PRONGRAM_VERSION}
  source:	<https://github.com/higedice/windows-command-line-tools>

 #{$PRONGRAM_DATE}
 HigeDice/ひげダイス
  e-mail:	<higedice@banjoyugi.net>
  blog:		<http://d.hatena.ne.jp/higedice/>
EOS
end






def rename_file(file_orig, file_new)
  begin
    File.rename(file_orig, file_new)
    puts 'Changed: ' + file_orig + ' -> ' + file_new
  rescue => err
    $stderr.puts 'Erorr: ' + file_orig + ': ' + err.message
  end
end





if ARGV.size < 3
  print_usage
  exit(-1)
end


done = {}
exp_from = ARGV.shift
str_to = ARGV.shift


ARGV[0..-1].each do |f|

  if File.directory? f		# Directory
    $stderr.puts f + ' is a directory.'
  else				# File
    f_new = File.join(File.dirname(f), File.basename(f).gsub(/#{exp_from}/, str_to))
    f = File.join(File.dirname(f), File.basename(f))
    if f_new != f and not done.key? f then
      rename_file(f, f_new)
      done[f] = true
    end
  end

end
