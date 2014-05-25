//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
control: A[ not User.FAIL U User.after_sas ]

/*

*/
A[] not deadlock

/*

*/
E<> User.after_sas

/*

*/
E<> User.FAIL

/*

*/
control: A[] not User.FAIL

/*

*/
A[] not User.FAIL
