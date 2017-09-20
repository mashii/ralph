1. wait message from acceptor or client socket or worker
    1.1. handle request from acceptor
        a. get socket
        b. put socket to queue
        c. put socket to poll to listen input message

    1.2. handle request from client
        a. get socket
        b. get data from socket buffer (uncomplete request last time)
        c. read from socket to tmp buffer
        d. handle requtest
            1. get a full request (can be configure)
            2. choose a worker (can be configure)
            3. put request to worker
        e. put the uncomplete data to socket buffer

    1.3. handle request from worker
        a. get socket
        b. get data from socket buffer (do not send last time)
        c. get data from worker
        d. try to send data to client
        e. put the left data to socket buffer
