import java.util.List;

import br.unb.graph.Graph;
import br.unb.graph.Node;

public class TestGraph {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("**Depth First Search**");
		dfsTest();
		
		System.out.println("\n**Breadth First Search**");
		bfsTest();
		
		System.out.println("\n**Topological Sort 1**");
		topologicalSortTest1();
		
		System.out.println("\n**Topological Sort 2**");
		topologicalSortTest2();
		
		System.out.println("\n**Topological Sort 3**");
		topologicalSortTest3();
	}
	
	public static void topologicalSortTest1(){
		Graph graph = new Graph();
		
		Node v1 = new Node("v1");
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		Node v7 = new Node("v7");
		
		graph.addNode(v1);
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		graph.addNode(v7);
		
		
		graph.addEdge(v1.getIndex(), v4.getIndex());
		graph.addEdge(v1.getIndex(), v5.getIndex());
		graph.addEdge(v1.getIndex(), v7.getIndex());
		graph.addEdge(v2.getIndex(), v3.getIndex());
		graph.addEdge(v2.getIndex(), v5.getIndex());
		graph.addEdge(v2.getIndex(), v6.getIndex());
		graph.addEdge(v3.getIndex(), v5.getIndex());
		graph.addEdge(v3.getIndex(), v4.getIndex());
		graph.addEdge(v4.getIndex(), v5.getIndex());
		graph.addEdge(v5.getIndex(), v6.getIndex());
		graph.addEdge(v5.getIndex(), v7.getIndex());
		graph.addEdge(v6.getIndex(), v7.getIndex());
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
	}
	
	public static void topologicalSortTest2(){
		Graph graph = new Graph();
		
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		
		graph.addEdge(v6.getIndex(), v2.getIndex());
		graph.addEdge(v2.getIndex(), v5.getIndex());
		graph.addEdge(v2.getIndex(), v3.getIndex());
		graph.addEdge(v5.getIndex(), v4.getIndex());
		graph.addEdge(v3.getIndex(), v4.getIndex());
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
	}
	
	public static void topologicalSortTest3(){
		Graph graph = new Graph();
		
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		
		graph.addEdge(v6.getIndex(), v2.getIndex());
		graph.addEdge(v2.getIndex(), v5.getIndex());
		graph.addEdge(v2.getIndex(), v3.getIndex());
		graph.addEdge(v5.getIndex(), v4.getIndex());
		graph.addEdge(v3.getIndex(), v4.getIndex());
		graph.addEdge(v4.getIndex(), v6.getIndex());
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
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



