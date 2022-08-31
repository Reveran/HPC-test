if [ $# -eq 0 ]
then
    printf "Usage:\n"$0" <Execution Mode>\n\n\tExecution Mode: (--sequential, --threading, --process), Defines the mode of parallelism.\nExample:\n\t"$0" --threading\n\tNote: \"--process\" flag requires root permissions due to maximum allocable shared memory.\n\n"
    exit
fi

if [ $1 = "--sequential" ]
then
    echo 'Dimencion de la Matriz, Tiempo de ejecucion (s)' > sequential.csv
    for mtx in 480 960 1920 3840 7680
    do
        echo $mtx, $(./linux-matrix $mtx 1 --sequential) >> sequential.csv
        echo "Done Matrix" $mtx"x"$mtx"."
    done
    exit
fi

if [ $1 = "--process" ]
then
    #printf "Setting maximum shared memory to 2GB. Requesting root permissions"
    #sudo sysctl -w kernel.shmmax=2147483648      
    #sudo sysctl -w kernel.shmall=524288
    echo 'Cantidad de Procesos, Dimencion de la Matriz, Tiempo de ejecucion (s)' > process.csv
    for thread in 2 4 6 8 12 16
    do
    	echo runing with $thread process.
        for mtx in 480 960 1920 3840 7680
        do
            echo $thread, $mtx, $(./linux-matrix $mtx $thread --process) >> process.csv
            echo "\tDone Matrix" $mtx"x"$mtx"."
        done
        echo "Done" $thread threads.
    done
    exit
fi

if [ $1 = "--threading" ]
then
    echo 'Cantidad de Hilos, Dimencion de la Matriz, Tiempo de ejecucion (s)' > threading.csv
    for thread in 2 4 6 8 12 16
    do
    	echo runing with $thread threads.
        for mtx in 480 960 1920 3840 7680
        do
            echo $thread, $mtx, $(./linux-matrix $mtx $thread --threading) >> threading.csv
            echo "\tDone Matrix" $mtx"x"$mtx"."
        done
        echo "Done" $thread threads.
    done
    exit
fi
printf "Bad Execution Mode.\nUsage:\n"$0" <Execution Mode>\n\n\tExecution Mode: (--sequential, --threading, --process), Defines the mode of parallelism.\nExample:\n\t"$0" --threading\nNote: \"--process\" flag requires root permissions due to maximum allocable shared memory.\n\n"
