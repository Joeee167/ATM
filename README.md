# C++ ATM System

## An ATM System that provides some functionalities such as Quick Withdraw , Normal Withdraw , Deposit and Check your balance.


This project was built to practice using files as a tool to save clients' info then perform operations on their balances then update this data in the file . It allows the client to simulate using an ATM System


# Features
![Login Screen](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-06-25%20133445.png)
![Main Menu](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-06-25%20134113.png)
* The client is firstly prompted to enter his account number and pin code which are used to search if this client already exists in the file which includes clients data.
* If the account number or pin code is not correct , the client is asked to re-enter them.
* If the client enters his account number and pin correctly , he is transfered to main menu screen to perform the available ATM operations.

![Quick Withdraw](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-06-25%20134424.png)
* The client can choose to withdraw one of the following amounts.
* If the amount dos not exceed the client's balance , the withdraw is performed and his balance is updated in the file.
* If the amount is more than the client's balance , the client is asked to enter another amount


![Normal withdraw](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-07-01%20124007.png)
![Normal withdraw](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-07-01%20124037.png)
* The client can enter any amount that is multiple of 5 only.
* If the entered amount is multiple of 5 and less than his current balance , the amount is withdrawn.
* If the amount is not multiple of 5 , the client is asked to enter another amount.

![Deposit](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-07-01%20124831.png)
![Deposit](https://github.com/Joeee167/ATM/blob/master/Screenshot%202024-07-01%20124937.png)
* The client is asked to enter a positive amount to deposit.
* After that , the client should confirm this transaction . Then , the client's balance is updated
