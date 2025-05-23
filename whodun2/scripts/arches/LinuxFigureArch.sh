
# figure out the architecture in play

uname_p=$(uname -m)
case "$uname_p" in
	(x86_64)
		echo x64
		;;
	(amd64)
		echo x64
		;;
	(i686-64)
		echo x64
		;;
	(*) echo oth;
esac


#	(i386)
#		echo x86
#		;;
#	(i686)
#		echo x86
#		;;
#	(athlon)
#		echo x86
#		;;
#	(i86pc)
#		echo x86
#		;;
#	(x86pc)
#		echo x86
#		;;
#	(arm)
#		echo arm
#		;;
#	(armv7l)
#		echo arm
#		;;
#	(armv6l)
#		echo arm
#		;;
#	(aarch64)
#		echo arm64
#		;;
#	(arm64)
#		echo arm64
#		;;

