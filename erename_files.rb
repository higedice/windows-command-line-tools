#!/usr/local/bin/ruby
#
#  rename_files.rb
#
#  2013/07/13	new
#		Is it better to get all filenames to rename first and then
#		rename?
#


$PRONGRAM_VERSION = '1.0.0'
$PRONGRAM_DATE = '2013/07/13'



def print_usage
  $stderr.puts <<EOS
Usage: ruby rename_files.rb PATTERN NEW_STRING <directorys>... <files>... 

This program *CANNOT* UNDO!

Search for PATTERN in files and each one's name in target directorys and
replace to NEW_STRING.
PATTERN is an extended regular expression.

Example: ruby rename_files.rb "foto of " "" . path/to/ "foto of 2013-07-12.jpg"

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
    $stderr.puts 'Erorr: ' + err.message
  end
end





if ARGV.size < 3
  print_usage
  exit(-1)
end


exp_from = ARGV.shift
str_to = ARGV.shift


ARGV[0..-1].each do |f|

  f = f == '.' ? './' : f

  if not File.directory? f	# File
    f_new = File.join(File.dirname(f), File.basename(f).gsub(/#{exp_from}/, str_to))
    f = File.join(File.dirname(f), File.basename(f))
    rename_file(f, f_new) unless f_new == f
  elsif f =~ /[\/\\]$/		# Directory with name ends '/' OR '\'
    Dir.foreach(f) do |f_orig|
      if File.directory? f_orig
        $stderr.puts f_orig + ' is a directory.' unless f_orig =~ /^\.\.?$/
      else
        f_new = f_orig.gsub(/#{exp_from}/, str_to)
        rename_file(f + f_orig, f + f_new) unless f_new == f_orig
      end
    end
  else				# Directory with name does not ends '/' OR '\'.
    $stderr.puts f + ' is a directory.'
  end

end
