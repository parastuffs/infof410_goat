//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
E<> User.After_SAS

/*

*/
control: A[] (User.After_SAS imply gateConf == 2)

/*
Cannot be in the SAS_Opened state if the door config is not 2.
Note that if we add the condition gateConf == 2, the query still holds. Indeed, even after having opened the second door, the user does not have to leave through it.
*/
control: A[ not(User.After_SAS) U (gateConf == 1 or gateConf == 0)]

/*
Sort dans le futur. C'est-\u00e0-dire que s'il est dans In_SAS, il finira par retourner dans Before_SAS.
*/
User.In_SAS --> (User.Before_SAS or User.After_SAS)

/*

*/
control: A[] (User.In_SAS imply (User.Before_SAS or User.After_SAS))

/*

*/
User.Before_SAS --> User.In_SAS

/*
Pas \u00e0 deux dans le sas.
*/
A[] User.In_SAS imply not(User2.In_SAS)

/*

*/
A[] not deadlock
