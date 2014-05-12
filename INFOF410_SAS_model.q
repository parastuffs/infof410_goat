//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
E<> User.After_SAS

/*

*/
User.After_SAS imply User.SAS_Opened

/*
Sort dans le futur.
*/
//NO_QUERY

/*

*/
A[] not deadlock

/*
Atteind After_SAS que si la carte a \u00e9t\u00e9 valid\u00e9e au moins une fois.
*/
control: A[ not(User.After_SAS) W User.SAS_Opened  ]

/*

*/
control: A<> User.After_SAS
