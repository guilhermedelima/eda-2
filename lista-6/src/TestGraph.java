import br.unb.graph.Graph;
import br.unb.graph.Node;

public class TestGraph {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		bfsTest();
	}
	
	public static void dfsTest(){
		
		Graph graph = new Graph();
		Node nodeA = new Node("A");
		Node nodeB = new Node("B");
		Node nodeC = new Node("C");
		Node nodeD = new Node("D");
		Node nodeE = new Node("E");
		graph.addNode(nodeA);
		graph.addNode(nodeB);
		graph.addNode(nodeC);
		graph.addNode(nodeD);
		graph.addNode(nodeE);
		
		graph.addEdge(nodeA.getIndex(), nodeB.getIndex());
		graph.addEdge(nodeB.getIndex(), nodeD.getIndex());
		graph.addEdge(nodeB.getIndex(), nodeC.getIndex());
		graph.addEdge(nodeC.getIndex(), nodeE.getIndex());
		graph.addEdge(nodeD.getIndex(), nodeC.getIndex());
		graph.addEdge(nodeE.getIndex(), nodeC.getIndex());
		
		graph.depthFirstSearch();
	}
	
	public static void bfsTest(){
		
		Graph graph = new Graph();
		
		Node n1 = new Node("Nó 1");
		Node n2 = new Node("Nó 2");
		Node n3 = new Node("Nó 3");
		Node n4 = new Node("Nó 4");
		Node n5 = new Node("Nó 5");
		Node n6 = new Node("Nó 6");
		Node n7 = new Node("Nó 7");
		
		graph.addNode(n1);
		graph.addNode(n2);
		graph.addNode(n3);
		graph.addNode(n4);
		graph.addNode(n5);
		graph.addNode(n6);
		graph.addNode(n7);
		
		graph.addEdge(n1.getIndex(), n5.getIndex());
		graph.addEdge(n1.getIndex(), n4.getIndex());
		graph.addEdge(n4.getIndex(), n5.getIndex());
		graph.addEdge(n4.getIndex(), n2.getIndex());
		graph.addEdge(n1.getIndex(), n2.getIndex());
		graph.addEdge(n2.getIndex(), n6.getIndex());
		graph.addEdge(n3.getIndex(), n7.getIndex());
		
		
		graph.breadthFirstSearch();
	}

}



