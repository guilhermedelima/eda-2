import br.unb.graph.Graph;
import br.unb.graph.Node;

public class TestGraph {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
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
		//graph.breadthFirstSearch();
	}

}



