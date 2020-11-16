# ATM
General Purpose ATM

To Compile. In root do
```
mkdir build && cd build
cmake ..
make
```

To Run in root folder do:
```
./build/atm_main
```

This example emulates basic functionality of an ATM. There are some assumptions that I have made during the process that I am enlisting here. These assumptions can be removed but I have made the choice to make the example easier and hence just focussed on functionality.

Three dummy accounts have been added for testing purposes (account no: 1,2,3). The card of account no one is assumed to be be always inserted. Every account gets a default pin of 1234. So when running the example the pin is 1234. I have designed this example for checkings account only. This can be easily extended to savings as well. The command line does ask for checkings vs savings however both do the same thing. The other options are self explanatory. I have also assumed that the inputs are always consistent.