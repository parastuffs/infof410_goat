//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5535), March 2014

/*

*/
E<> User.After_SAS

/*

*/
not(User.SAS_Opened) --> not(User.After_SAS)

/*
Cannot be in the SAS_Opened state if the door config is not 2.
Note that if we add the condition gateConf == 2, the query still holds. Indeed, even after havin opened the second door, the user does not have to leave through it.
*/
control: A[ not(User.SAS_Opened) U (gateConf == 1 or gateConf == 0) ]

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
