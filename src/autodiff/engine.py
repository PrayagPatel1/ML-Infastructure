# Implementation Date: May 10, 2026
# Author: PrayagPatel1 
# Topic: Automatic Differentiation - Reverse Mode

class Primal:
    """
    Represents a node within a computational graph for representing Mathematical
    expressions. This will carry out reverse mode automatic differentiation.

    data: float - Represents the data that a node possess after an operation has
                  been applied to it. 
    grad: float - Represents the gradient accumulation of the current node. 
    _op: str - Represents the operation used to modify the <data>.
    _parents: set() - Represents the current Primal parents. 
    """
    data: float
    grad: float

    def __init__(self, data: float, label: str, _op="", _parents=None):
        self.data = data
        self.grad = 0.0
        self.label = label

        self._op = _op
        if _parents is not None:
            self._parents = _parents
        else: 
            self._parents = set()

        self._backward = lambda: None

    # Implementation of topo_sort() was done via ChatGPT.
    # Prompt: Can you implement a topological sort for reverse mode auto differentiation
    def topo_sort(self) -> list[Primal]:
        """
        Returns a list of all primals within the compute graph ordered 
        topologically. 
        """
        visited = set()
        topo_elems = []

        def build(primal):
            if primal not in visited:
                visited.add(primal)
            
                for child in primal._parents:
                    build(child)

                topo_elems.append(primal)
        
        build(self)
        return topo_elems

    def backward(self):
        """
        Performs reverse mode auto differentiation
        """
        topo_elems = self.topo_sort()
        self.grad = 1.0 

        for primal in reversed(topo_elems):
            primal._backward()
    
    # === Binary Operations === 
    def __add__(self, other):
        if not isinstance(other, Primal):
            other = Primal(other, "")

        out = Primal(self.data + other.data, "",  "+", {self, other})
        
        def _backward():
            self.grad += out.grad * 1.0 
            other.grad += out.grad * 1.0
        
        out._backward = _backward
        return out
    
    def __sub__(self, other):
        if not isinstance(other, Primal):
            other = Primal(other, "")

        out = Primal(self.data - other.data, "",  "-", {self, other})

        def _backward():
            self.grad += out.grad * 1.0 
            other.grad += out.grad * -1.0

        out._backward = _backward
        return out
    
    def __mul__(self, other):
        if not isinstance(other, Primal):
            other = Primal(other, "")

        out = Primal(self.data * other.data, "", "*", {self, other})

        def _backward():
            self.grad += out.grad * other.data
            other.grad += out.grad * self.data

        out._backward = _backward
        return out
    
    def __truediv__(self, other):
        if not isinstance(other, Primal):
            other = Primal(other, "")

        out = Primal(self.data / other.data, "", "/", {self, other})

        def _backward():
            if other.data != 0:
                self.grad += out.grad * (1 / other.data)
                self.other += out.grad * ((-self.data) / (other.data ** 2))
        
        out._backward = _backward
        return out
    
    # === Unary Operation === 
    def __pow__(self, other):
        pass

    def tanh(self):
        pass
    
    def __repr__(self):
        return f"Value(data={self.data}, \n op={self._op}, \n parents={self._parents}, \n label={self.label})"

# class CompGraph:
#     """
#     Represents the computational graph data structure which is a directed acylic
#     graph (DAG). 

#     primals - A list of Primal nodes that have been defined prior.
#     nodes - A collection of nodes that is the graph.
#     """

#     primals: list[Primal]
#     nodes: dict[str: Primal]

#     def __init__(self, primals: list[Primal]):
#         self.primals = primals
#         self.nodes = {};

#         for primal in self.primals:

#             if (not primal.getParents()):
#                 self.nodes[primal.label] = []
            
#             # The case where the primal has parents
#             if (primal.label in self.nodes):
#                 for parent in primal.getParents():
#                     self.nodes[primal.label].append(parent)
#             else:
#                 self.nodes[primal.label] = []
#                 for parent in primal.getParents():
#                     self.nodes[primal.label].append(parent)
    
#     def __repr__(self):
#         strings = []
#         for label, primals in self.nodes.items():
#             connections = []
#             for primal in primals:
#                 connections.append(primal)
            
#             strings.append(f"{label} -> {connections}")
        
#         return "CompGraph: \n" + "\n".join(strings)




            


