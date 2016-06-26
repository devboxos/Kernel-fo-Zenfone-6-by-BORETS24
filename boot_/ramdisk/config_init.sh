# software configuration related boot actions

# project ID
# 0 - 4 : A500CG
# 5 , 7 : A600CG
# 6     : A502CG

PROJID_DETECT=$(cat /sys/module/intel_mid_sfi/parameters/project_id)
COUNTRY_CODE=$(./system/bin/country_code)
SIM_ID=$(cat /proc/sim_id)

log -p i -t config_init "PROJID: $PROJID_DETECT"
log -p i -t config_init "COUNTRY_CODE: $COUNTRY_CODE"

if [ -n "$PROJID_DETECT" ]; then
	if [ "$SIM_ID" -eq 1 ]; then

		if [ "$PROJID_DETECT" -ge 0 -a "$PROJID_DETECT" -le 4 ]; then
			echo "DSDS_A500CG" > /config/local_config

		elif [ "$PROJID_DETECT" -eq 5 -o "$PROJID_DETECT" -eq 7 ]; then

			if [ "$COUNTRY_CODE" = "TH" ]; then
				echo "DSDS_A600CG_TH" > /config/local_config
			else
				echo "DSDS_A600CG" > /config/local_config
			fi
		elif [ "$PROJID_DETECT" -eq 6 ]; then
			echo "DSDS_A502CG" > /config/local_config

		else
			echo "DSDS" > /config/local_config
		fi

	elif [ "$SIM_ID" -eq 0 ]; then

        if [ "$PROJID_DETECT" -ge 0 -a "$PROJID_DETECT" -le 4 ]; then
			echo "SINGLE_A500CG" > /config/local_config

		elif [ "$PROJID_DETECT" -eq 5 -o "$PROJID_DETECT" -eq 7 ]; then

			if [ "$COUNTRY_CODE" = "TH" ]; then
				echo "SINGLE_A600CG_TH" > /config/local_config
			else
				echo "SINGLE_A600CG" > /config/local_config
			fi
		elif [ "$PROJID_DETECT" -eq 6 ]; then
			echo "SINGLE_A502CG" > /config/local_config

        else
			echo "SINGLE" > /config/local_config
		fi

	else
		echo "DSDS" > /config/local_config
	fi
else
        echo "DSDS" > /config/local_config
fi

CONFIG_PATH=/local_cfg
PROPS_FILE=init.props

# Get selected software configuration

config=`cat /config/local_config`

#ln -s /system/etc/catalog/$config /local_cfg
mount -o bind /system/etc/catalog/$config /local_cfg

log -p i -t config_init "Activating configuration $config"

# Boot flow has to be suspended so that the ramdisk is not re-mounted r/o.
# Signal configuration is done so that boot flow can resume.
#echo > /config_init.done

# Set properties for the selected configuration

# read all FeatureTeam's init.props file
for f in /local_cfg/*/init.props
do
    while read l; do

        # Ignore empty lines and comments
        case "$l" in
            ''|'#'*)
                continue
                ;;
        esac

        # Set property
        setprop `echo ${l/=/ }`

    done < $f
done
