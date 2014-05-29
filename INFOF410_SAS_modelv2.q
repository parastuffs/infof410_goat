//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
E<> (User.in_sas and User2.in_sas)

/*
If User is in the sas, User2 can't be.
*/
A[] User.in_sas imply not(User2.in_sas)

/*

*/
A[] not deadlock

/*

*/
E<> User.after_sas

/*
Here, we play in a controller game. We play the controller while Tiga plays the environment.
Previously, the condition "A[] not User.FAIL" was not satisfied, we did not have the controller collaboration.
But now, with the help of the controller, it _is_ satisfied, we won't ever access User.FAIL
*/
control: A[] not(User.FAIL or User2.FAIL)

/*

*/
A[] not (User.FAIL)
