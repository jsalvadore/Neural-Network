# Neural-Network
A depot for building my own personal neural network routines. 

####Header files

* vec - class implementing mathematical vectors and some associated machinery.
   
* matrix - class implementing mathematical matrices and some associated machinery.
  
* nnet - Class for representing and training neural networks.


####Functionality
There are two major functions of the neural network class, training and prediction.
In training, you pass the training data, a validation set, a learning rate, and
a maximum number of iterations. The network will then under-go fixed-rate gradient
descent using backpropagation to minimize the in-sample error. While this is occuring,
a validation set is regularly checked for early-stopping criteria.

Once a network is trained, it can be used for prediction. One should pass an unlabeled
test data set to the .train() method which will conduct forward propagation to produce
predictions for each data point. The returned vector of predictions can then be compared
to the true labels to assess error. 

####Considerations
There are a few technical caveats to using these routines. First, one needs a data set,
typically obtained from a csv. I've included a helper function for reading csv's in the
nnet implementation, but one can do this however. The data set should be split off from
its labels, as is the case for the validation and testing sets. All labels should be in
{1, -1}. Zero labels will break the training routine! When initializing your architecture,
you should build a vector d from scratch. The first number in d should be the dimension 
of your input data. For the middle values, one can pick any desired hyperparamaters. For 
the final value, it should always be 1 otherwise predictions won't be made properly. 

