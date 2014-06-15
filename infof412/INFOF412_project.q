//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
A<> not(User.FAIL or User2.FAIL)

/*
Both users are never in the sas at the same time.
*/
A[] not(User.in_sas and User2.FAIL)

/*

*/
A[] not deadlock

/*

*/
E<> User.after_sas

/*

*/
Sas.init_sas --> Sas.idle

/*
Here, we play in a controller game. We play the controller while Tiga plays the environment.
Previously, the condition "A[] not User.FAIL" was not satisfied, we did not have the controller collaboration.
But now, with the help of the controller, it _is_ satisfied, we won't ever access User.FAIL
*/
control: A[] not(User.FAIL or User2.FAIL)

/*

*/
A[] not(User.FAIL or User2.FAIL)
