infof410_goat
=============

INFOF410 - Project GOAT


We should have a synchronization sent from the user and received by the
controller, but not the other way around.
Indeed, when the user crosses the first infrared, we want the controller
to take immediate action, hence the sync.
On the other hand, when the controller open the second door, the user
is not compelled to leave the SAS through it just yet. In this case,
we better have a boolean variable activated by the controller allowing
the user to get the frack out if he wishes.

UppAal Tiga tips
----------------

* You can make several updates at the same time by seperating them with
commas.
* You can use logical operators in guards: || and &&.
