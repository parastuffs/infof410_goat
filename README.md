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

>We want the environnement to be able to loose. So `E<> User.FAIL` should
be satisfied. But, with the cooperation of the controller, we
want `control: A[] not User.FAIL` to be satisfied as well, that is with 
the help of the controller, we
cannot loose the game.

The paragraph just above may be just bullshit. Indeed, the transition
to User.FAIL state is a controllable one. So no shit that with the help
of the controller, we will never take that transition!

The only solution here is to force the SAS model to send a sync signal
when the timer is out by adding a gard on SAS.handling_user state.

UppAal Tiga tips
----------------

* You can make several updates at the same time by seperating them with
commas.
* You can use logical operators in guards: || and &&.
* ~~We cannot take a transition with a sync signal if the corresponding
node is not in a state waiting for it.~~ So not true.

Current State
-------------

User:

![User](https://raw.githubusercontent.com/parastuffs/infof410_goat/master/User_model.png)

SAS:

![SAS](https://raw.githubusercontent.com/parastuffs/infof410_goat/master/SAS_model.png)
