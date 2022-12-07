if [ -z $1 ]; then echo "Debe indicarse si se va a activar (1) o desactivar (0) los procesadores"
else
	cd /sys/devices/system/cpu
	for dir in cpu*; do
		if [ -f ./$dir/online ]; then echo $1 | tee ./"$dir"/online; fi
	done
fi
