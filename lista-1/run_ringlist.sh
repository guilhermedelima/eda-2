LOG_FILE=log/result.txt

make ringlist > /dev/null 2>&1

echo -e "======================================\nRunning Binary Search\n======================================" > $LOG_FILE
bin/ringlist 10 10 1 >> $LOG_FILE
bin/ringlist 25 45 1 >> $LOG_FILE
bin/ringlist 50 70 1 >> $LOG_FILE
bin/ringlist 100 345 1 >> $LOG_FILE
bin/ringlist 500 655 1 >> $LOG_FILE
bin/ringlist 1000 1200 1 >> $LOG_FILE
bin/ringlist 10000 12300 1 >> $LOG_FILE
bin/ringlist 100000 10500 1 >> $LOG_FILE
bin/ringlist 1000000 987450 1 >> $LOG_FILE
bin/ringlist 1000000 987451 1 >> $LOG_FILE

echo -e "\n======================================\nRunning Interpolation Search\n======================================" >> $LOG_FILE
bin/ringlist 10 10 2 >> $LOG_FILE
bin/ringlist 25 45 2 >> $LOG_FILE
bin/ringlist 50 70 2 >> $LOG_FILE
bin/ringlist 100 345 2 >> $LOG_FILE
bin/ringlist 500 655 2 >> $LOG_FILE
bin/ringlist 1000 1200 2 >> $LOG_FILE
bin/ringlist 10000 12300 2 >> $LOG_FILE
bin/ringlist 100000 10500 2 >> $LOG_FILE
bin/ringlist 1000000 987450 2 >> $LOG_FILE
bin/ringlist 1000000 987451 1 >> $LOG_FILE

exit 0