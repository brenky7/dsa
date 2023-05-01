import string.SplitFunction;
import string.getVariables;
import string.orderShuffle;
import tree.*;

import java.util.HashMap;

public class Main {
    public static HashMap<String, node> nodeMap = new HashMap<String, node>();
    public static void main(String[] args) {

        nodeMap.put("1", new node("1", '1'));
        nodeMap.put("0", new node("0", '0'));
        bdd tree = BDDcreate("!A!CDE!FGHIJ+!A!B!DEFGH!IK+A!B!CDE!FG!HI!JL+ABC!DEFGH!IJ!KM+!A!B!C!DEFGHIJKL+A!BCD!EFGH!IJK!L!M+!ABC!D!EFGHIJ!K!L!M+!ABC!DE!F!GHIJKL+A!B!C!DEFGH!IJKL!M+!ABCD!E!F!GHIJK!L!M+A!BCDEFG!HIJK!L!M+!ABC!DEFGH!IJKLM+AB!CDEFGHIJKLM+!A!BCDEFGHI!JKLM+A!B!C!DE!FGHIJ!KLM", "ABCDEFGHIJKLM");
        //bdd tree = BDDcreate_with_best_order("!A!CDE!FGHIJ+!A!B!DEFGH!IK+A!B!CDE!FG!HI!JL+ABC!DEFGH!IJ!KM+!A!B!C!DEFGHIJKL+A!BCD!EFGH!IJK!L!M+!ABC!D!EFGHIJ!K!L!M+!ABC!DE!F!GHIJKL+A!B!C!DEFGH!IJKL!M+!ABCD!E!F!GHIJK!L!M+A!BCDEFG!HIJK!L!M+!ABC!DEFGH!IJKLM+AB!CDEFGHIJKLM+!A!BCDEFGHI!JKLM+A!B!C!DE!FGHIJ!KLM");
        printTree(tree.root, 0);
        System.out.println(tree.numberOfNodes);
        System.out.println(BDD_use(tree, "0000111101111"));
    }

    public static bdd BDDcreate(String function, String order){
        bdd tree = new bdd();
        tree.root = BDDaddNodes(function, order, 0);
        tree.numberOfVariables = order.length();
        if (tree.root.function == "0"){
            nodeMap.remove("1");
            tree.numberOfNodes = nodeMap.size()-1;
        }
        else if (tree.root.function == "1"){
            nodeMap.remove("0");
            tree.numberOfNodes = nodeMap.size()-1;
        }
        else{
            tree.numberOfNodes = nodeMap.size();
        }
        return tree;
    }

    public static node BDDaddNodes(String function, String order, int index){
        if (function.equals("1")){
            return nodeMap.get("1");
        }
        if (index == order.length()){
            if (function.equals("1")){
                return nodeMap.get("1");
            }
            else if (function.equals("0")){
                return nodeMap.get("0");
            }
            else {
                System.out.println(function);
                return null;
            }
        }
        else {
            if (nodeMap.containsKey(function)){
                return nodeMap.get(function);
            }
            else {
                nodeMap.put(function, new node(function, order.charAt(index)));
                String[]next = {" ", " "};
                while (next[0].equals(next[1])){
                    next = SplitFunction.split(function, order.charAt(index));
                    if (!next[0].equals(next[1])){
                        break;
                    }
                    if (next[0].equals("1")){
                        return nodeMap.get("1");
                    }
                    else if (next[0].equals("0")){
                        return nodeMap.get("0");
                    }
                    else  {
                        index++;
                    }

                }
                nodeMap.get(function).left = BDDaddNodes(next[0], order, index + 1);
                nodeMap.get(function).right = BDDaddNodes(next[1], order, index + 1);
                return nodeMap.get(function);
            }
        }
    }
    public static bdd BDDcreate_with_best_order(String function){
        bdd tree = new bdd();
        String variables = getVariables.get(function);
        String[] orders = orderShuffle.shuffle(variables);
        double minNodes = Double.POSITIVE_INFINITY;
        for (String i : orders){
            bdd demoTree = BDDcreate(function, i);
            if (tree.numberOfNodes < minNodes){
                minNodes = tree.numberOfNodes;
                tree = demoTree;
            }
        }
        return tree;
    }
    public static void printTree(node root, int level) {
        if (root != null) {
            printTree(root.right, level + 1);
            System.out.println(" ".repeat(4 * level) + "-> " + root.function);
            printTree(root.left, level + 1);
        }
    }
    public static int BDD_use(bdd tree, String input){ //this algorithm traverses the tree and returns the output
        node current = tree.root;
        int index = 0;
        while (current != null){
            if (input.charAt(index) == '0'){
                current = current.left;
            }
            else if (input.charAt(index) == '1') {
                current = current.right;
            }
            else {
                System.out.println("Invalid input");
                return -1;
            }
            if (current.function.equals("0") || current.function.equals("1")){
                return Integer.parseInt(current.function);
            }
            index++;
        }
        return Integer.parseInt(current.function);
    }
}