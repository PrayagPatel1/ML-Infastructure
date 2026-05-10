# Implementation Date: May 10, 2026
# Author: PrayagPatel1 
# Topic: Class that represents the nodes and the computational graph itself

class Primal:
    """
    Represents a node within a computational graph for representing Mathematical
    expressions. 

    data: float - Represents the data that a node possess after an operation has
                  been applied to it. 
    """
    data: float

    def __init__(self, data: float, label: str, _op="", _parents={}):
        self.data = data
        self._op = _op
        self._parents = _parents
        self.label = label
    
    def __repr__(self):
        return f"Value(data={self.data}, \n op={self._op}, \n parents={self._parents}, \n label={self.label})"
    
    def __add__(self, other):
        return Primal(self.data + other.data, "",  "+", {self, other})
    
    def __sub__(self, other):
        return Primal(self.data - other.data, "",  "-", {self, other})
    
    def __mul__(self, other):
        return Primal(self.data * other.data, "", "*", {self, other})
    
    def __truediv__(self, other):
        return Primal(self.data / other.data, "", "/", {self, other})
    
    def getOp(self) -> str:
        """
        Returns the operator of a node as a string.
        """
        return self._op

    def getParents(self) -> set:
        """
        Returns the parents of the current node as a set.
        """
        return self._parents

class CompGraph:
    """
    Represents the computational graph data structure which is a directed acylic
    graph (DAG). 

    primals - A list of Primal nodes that have been defined prior.
    nodes - A collection of nodes that is the graph.
    """

    primals: list[Primal]
    nodes: dict[str: primals]

    def __init__(self, primals: list[Primal]):
        self.primals = primals
        self.nodes = {};

        for primal in self.primals:

            if (not primal.getParents()):
                self.nodes[primal.label] = []
            
            # The case where the primal has parents
            if (primal.label in self.nodes):
                for parent in primal.getParents():
                    self.nodes[primal.label].append(parent)
            else:
                self.nodes[primal.label] = []
                for parent in primal.getParents():
                    self.nodes[primal.label].append(parent)
    
    def __repr__(self):
        strings = []
        for label, primals in self.nodes.items():
            connections = []
            for primal in primals:
                connections.append(primal)
            
            strings.append(f"{label} -> {connections}")
        
        return "CompGraph: \n" + "\n".join(strings)

                

            

            


