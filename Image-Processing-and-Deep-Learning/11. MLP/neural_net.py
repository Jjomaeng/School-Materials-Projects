from __future__ import print_function

import numpy as np
import matplotlib.pyplot as plt
import random

class TwoLayerNet(object):
  """
  A two-layer fully-connected neural network. The net has an input dimension of
  N, a hidden layer dimension of H, and performs classification over C classes.
  We train the network with a softmax loss function and L2 regularization on the
  weight matrices. The network uses a ReLU nonlinearity after the first fully
  connected layer.

  In other words, the network has the following architecture:

  input - fully connected layer - ReLU - fully connected layer - softmax

  The outputs of the second fully-connected layer are the scores for each class.
  """

  def __init__(self, input_size, hidden_size, output_size, std=1e-4):
    """
    Initialize the model. Weights are initialized to small random values and
    biases are initialized to zero. Weights and biases are stored in the
    variable self.params, which is a dictionary with the following keys:

    W1: First layer weights; has shape (D, H)
    b1: First layer biases; has shape (H,)
    W2: Second layer weights; has shape (H, C)
    b2: Second layer biases; has shape (C,)

    Inputs:
    - input_size: The dimension D of the input data.
    - hidden_size: The number of neurons H in the hidden layer.
    - output_size: The number of classes C.
    """
	
	# np.random.randn(shape)
	# - Return a sample (or samples) from the “standard normal” distribution following shape
    self.params = {}
    self.params['W1'] = std * np.random.randn(input_size, hidden_size)
    self.params['b1'] = np.zeros(hidden_size)
    self.params['W2'] = std * np.random.randn(hidden_size, output_size)
    self.params['b2'] = np.zeros(output_size)

  def loss(self, X, y=None, reg=0.0):
    """
    Compute the loss and gradients for a two layer fully connected neural
    network.

    Inputs:
    - X: Input data of shape (N, D). Each X[i] is a training sample.
    - y: Vector of training labels. y[i] is the label for X[i], and each y[i] is
      an integer in the range 0 <= y[i] < C. This parameter is optional; if it
      is not passed then we only return scores, and if it is passed then we
      instead return the loss and gradients.
    - reg: Regularization strength.

    Returns:
    If y is None, return a matrix scores of shape (N, C) where scores[i, c] is
    the score for class c on input X[i].

    If y is not None, instead return a tuple of:
    - loss: Loss (data loss and regularization loss) for this batch of training
      samples.
    - grads: Dictionary mapping parameter names to gradients of those parameters
      with respect to the loss function; has the same keys as self.params.
    """
    # Unpack variables from the params dictionary
    W1, b1 = self.params['W1'], self.params['b1']
    W2, b2 = self.params['W2'], self.params['b2']

    # Compute the forward pass
    scores = None
    #############################################################################
    # TODO: Perform the forward pass, computing the class scores for the input. #
    # Store the result in the scores variable, which should be an array of      #
    # shape (N, C).                                                             #
    #############################################################################
	# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    
    #1st-fully connected
    x = X
    s1 = np.dot(x,W1) + b1
    
    #Lelu
    mask = (s1 <= 0)
    out = s1.copy()
    out[mask] = 0
    
    #2nd - fully connected
    s2 = np.dot(out,W2) + b2
    
    
    #softmax
    if s2.ndim == 2:
        s2 = s2.T
        s2 = s2 - np.max(s2, axis=0)
        scores = np.exp(s2) / np.sum(np.exp(s2), axis=0)
        scores = scores.T

    else :
        s2 = s2 - np.max(s2) 
        scores = np.exp(s2) / np.sum(np.exp(s2))
    
	
	# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    #############################################################################
    #                              END OF YOUR CODE                             #
    #############################################################################
 
    # If the targets are not given then jump out, we're done
    if y is None:
      return scores

    # Compute the loss
    loss = None
    #############################################################################
    # TODO: Finish the forward pass, and compute the loss. This should include  #
    # both the data loss and L2 regularization for W1 and W2. Store the result  #
    # in the variable loss, which should be a scalar. Use the Softmax           #
    # classifier loss.                                                          #
    #############################################################################
	# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
	
    
    if scores.ndim == 1:
        y = y.reshape(1, y.size)
        scores = scores.reshape(1, scores.size)
        
    
    if y.size == scores.size:
        y = y.argmax(axis=1)
             
    batch_size = scores.shape[0]
    loss = -np.sum(np.log(scores[np.arange(batch_size), y] + 1e-7)) / batch_size
 
	
	# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    #############################################################################
    #                              END OF YOUR CODE                             #
    #############################################################################

    # Backward pass: compute gradients
    grads = {}
    #############################################################################
    # TODO: Compute the backward pass, computing the derivatives of the weights #
    # and biases. Store the results in the grads dictionary. For example,       #
    # grads['W1'] should store the gradient on W1, and be a matrix of same size #
    #############################################################################
	# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
	
    # Let z be the result after W * X, z after activation function becomes y.
    
    #softmax_backward
    batch_size = y.shape[0]
    if y.size == scores.size: # 정답 레이블이 원-핫 인코딩 형태일 때
        dx = (scores - y) / batch_size
    else:
        dx = scores.copy()
        dx[np.arange(batch_size), y] -= 1
        dx = dx / batch_size
    
    #2nd-fully connected backward
    dx2 = np.dot(dx, W2.T)
    grads['W2'] = np.dot(X.T, dx)
    grads['b2'] = np.sum(dx, axis=0) 
    
    #relu backward
    dx2[mask] = 0
    dx3 = dx2
    
    #1st-fully connected backward
    dx4 = np.dot(dx3,W1.T)
    grads['W1'] = np.dot(X.T, dx3)
    grads['b1']= np.sum(dx3, axis=0)
        

	
	# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    #############################################################################
    #                              END OF YOUR CODE                             #
    #############################################################################

    return loss, grads

  def train(self, X, y, X_val, y_val,
            learning_rate=1e-3, learning_rate_decay=0.95,
            reg=5e-6, num_iters=100,
            batch_size=200, verbose=False):
    """
    Train this neural network using stochastic gradient descent.

    Inputs:
    - X: A numpy array of shape (N, D) giving training data.
    - y: A numpy array f shape (N,) giving training labels; y[i] = c means that
      X[i] has label c, where 0 <= c < C.
    - X_val: A numpy array of shape (N_val, D) giving validation data.
    - y_val: A numpy array of shape (N_val,) giving validation labels.
    - learning_rate: Scalar giving learning rate for optimization.
    - learning_rate_decay: Scalar giving factor used to decay the learning rate
      after each epoch.
    - reg: Scalar giving regularization strength.
    - num_iters: Number of steps to take when optimizing.
    - batch_size: Number of training examples to use per step.
    - verbose: boolean; if true print progress during optimization.
    """
    num_train = X.shape[0]
    iterations_per_epoch = max(num_train / batch_size, 1)

    # Use SGD to optimize the parameters in self.model
    loss_history = []
    train_acc_history = []
    val_acc_history = []

    for it in range(num_iters):
      X_batch = None
      y_batch = None

      #########################################################################
      # TODO: Create a random minibatch of training data and labels, storing  #
      # them in X_batch and y_batch respectively.                             #
	  # - See [ np.random.choice ]											  #
      #########################################################################
	  # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
	  
      for i in range(int(iterations_per_epoch)):
            batch_mask = np.random.choice(num_train,batch_size)
            x_batch = X[batch_mask]
            t_batch = y[batch_mask]
	  
	  # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
      #########################################################################
      #                             END OF YOUR CODE                          #
      #########################################################################
	  
      # Compute loss and gradients using the current minibatch
      loss, grads = self.loss(X_batch, y=y_batch, reg=reg) # loss function you completed above
      loss_history.append(loss)
	  
      #########################################################################
      # TODO: Use the gradients in the grads dictionary to update the         #
      # parameters of the network (stored in the dictionary self.params)      #
      # using stochastic gradient descent. You'll need to use the gradients   #
      # stored in the grads dictionary defined above.                         #
      #########################################################################
	  # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
	  
      for key in ("W1","b1","W2","b2"):
        self.params[key] -= learning_rate * grad[key]
	  
	  # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
      #########################################################################
      #                             END OF YOUR CODE                          #
      #########################################################################

	  # print loss value per 100 epoch
      if verbose and it % 100 == 0:
        print('iteration %d / %d: loss %f' % (it, num_iters, loss))

      # Every epoch, check train and val accuracy and decay learning rate.
      if it % iterations_per_epoch == 0:
        # Check accuracy
        train_acc = (self.predict(X_batch) == y_batch).mean()
        val_acc = (self.predict(X_val) == y_val).mean()
        train_acc_history.append(train_acc)
        val_acc_history.append(val_acc)

        # Decay learning rate
        learning_rate *= learning_rate_decay

    return {
      'loss_history': loss_history,
      'train_acc_history': train_acc_history,
      'val_acc_history': val_acc_history,
    }

  def predict(self, X):
    """
    Use the trained weights of this two-layer network to predict labels for
    data points. For each data point we predict scores for each of the C
    classes, and assign each data point to the class with the highest score.

    Inputs:
    - X: A numpy array of shape (N, D) giving N D-dimensional data points to
      classify.

    Returns:
    - y_pred: A numpy array of shape (N,) giving predicted labels for each of
      the elements of X. For all i, y_pred[i] = c means that X[i] is predicted
      to have class c, where 0 <= c < C.
    """
    y_pred = None

    ###########################################################################
    # TODO: Implement this function; it should be VERY simple!                #
	# perform forward pass and return index of maximum scores				  #
    ###########################################################################
	# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    scores = self.loss(X)
    y_pred = argmax(scroes)
     
	
	# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    ###########################################################################
    #                              END OF YOUR CODE                           #
    ###########################################################################

    return y_pred


