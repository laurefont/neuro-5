# Source neuro-5

## About 

Applications 

## Classes Structure

![alt text](../doc/diagram_apps.png "Diagram of applications")

## Theoretical explanation 

### General differential equation


![alt text](../doc/GE_RI.png "General equation")

with![alt text](../doc/Jij.PNG "test")the postsynaptic potential amplitude,
![alt text](../doc/delta.PNG "test")the dirac function,
![alt text](../doc/tkj.PNG "test")is the emission time of kth spike at
neuron j and D the transmission delay.


### Types of solutions

#### Forward Euler (explicit method)

![alt text](../doc/FE.png "Forward Euler´s formula")

#### Backward Euler (implicit method)

![alt text](../doc/BE.png "Backward Euler´s formula")

#### Analytical solution 

![alt text](../doc/as_fs.png "Analytical solution´s formula")

We discard the charging part of (1) solution. Thus, we consider that the
neuron is able to steeply rise its potential when there is an input of
current (modeled by equation (2)). Equation (3) comprises the discharge
of the capacity by an exponential decay with the time contant ![alt text](../doc/tau.png "tau"). 

#####Fixed-time stepping solutions

A simpler and faster way of stimulating those neurons with the same model
to use equation (1) and solve it with a fixed-time step. There are two
solutions. One can either compute the explicit solution (4) or the
implicit solution (5). Explicit method relies on everything that happened
before the time ![alt text](../doc/t.png "t") ![alt text](../doc/vt_1.png "velocity at t-1") and ![alt text](../doc/I.png "Current") to compute ![alt text](../doc/vt.png "Instantaneous Velocity")
whereas implicit solution starts where ![alt text](../doc/vt.png "Instantaneous velocity") is on both sides of the equations.

Fixed-time stepping explicit solution

![alt text](../doc/es_fs.png "Explicit solution")

Fixed-time stepping implicit solution

![alt text](../doc/is_fs.png "Explicit solution")


## References

* Brunel´s 2000 model
