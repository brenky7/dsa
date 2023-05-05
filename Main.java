import string.*;
import testStuff.*;
import tree.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Main {
    public static HashMap<String, node> nodeMap = new HashMap<String, node>();
    public static void main(String[] args) {

        //bdd tree = BDDcreate("!A!CDE!FGHIJ+!A!B!DEFGH!IK+A!B!CDE!FG!HI!JL+ABC!DEFGH!IJ!KM+!A!B!C!DEFGHIJKL+A!BCD!EFGH!IJK!L!M+!ABC!D!EFGHIJ!K!L!M+!ABC!DE!F!GHIJKL+A!B!C!DEFGH!IJKL!M+!ABCD!E!F!GHIJK!L!M+A!BCDEFG!HIJK!L!M+!ABC!DEFGH!IJKLM+AB!CDEFGHIJKLM+!A!BCDEFGHI!JKLM+A!B!C!DE!FGHIJ!KLM", "ABCDEFGHIJKLM");
        //bdd tree = BDDcreate_with_best_order("!A!CDE!FGHIJ+!A!B!DEFGH!IK+A!B!CDE!FG!HI!JL+ABC!DEFGH!IJ!KM+!A!B!C!DEFGHIJKL+A!BCD!EFGH!IJK!L!M+!ABC!D!EFGHIJ!K!L!M+!ABC!DE!F!GHIJKL+A!B!C!DEFGH!IJKL!M+!ABCD!E!F!GHIJK!L!M+A!BCDEFG!HIJK!L!M+!ABC!DEFGH!IJKLM+AB!CDEFGHIJKLM+!A!BCDEFGHI!JKLM+A!B!C!DE!FGHIJ!KLM");
        /*bdd tree = BDDcreate("!AB!C+B+B!C+A!B!C+!BC+!ABC", "ABC");
        System.out.println("Number of nodes: " + tree.numberOfNodes);
        printTree(tree.root, 0);
        for (String i : nodeMap.keySet()){
            System.out.println(i);
        }*/
        testSpravnosti(13);
    }

    public static bdd BDDcreate(String function, String order){
        nodeMap.put("1", new node("1", '1'));
        nodeMap.put("0", new node("0", '0'));
        bdd tree = new bdd(order);
        tree.root = BDDaddNodes(function, order, 0);
        tree.numberOfVariables = order.length();
        if ( tree.root.left != null && tree.root.right != null && tree.root.left.function.equals(tree.root.right.function)){
            tree.root = tree.root.left;
            tree.root.left = null;
            tree.root.right = null;
        }
        if (tree.root.function == "0"){
            nodeMap.clear();
            nodeMap.put("0", tree.root);
            tree.numberOfNodes = nodeMap.size();
        }
        else if (tree.root.function == "1"){
            nodeMap.clear();
            nodeMap.put("1", tree.root);
            tree.numberOfNodes = nodeMap.size();
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
                        nodeMap.remove(function);
                        return nodeMap.get("1");
                    }
                    else if (next[0].equals("0")){
                        nodeMap.remove(function);
                        return nodeMap.get("0");
                    }
                    else  {
                        index++;
                        nodeMap.get(function).variable = order.charAt(index);
                    }

                }
                nodeMap.get(function).left = BDDaddNodes(next[0], order, index + 1);
                nodeMap.get(function).right = BDDaddNodes(next[1], order, index + 1);
                if (nodeMap.get(function).left == nodeMap.get(function).right){
                    node temp = nodeMap.get(function);
                    nodeMap.get(function).function = nodeMap.get(function).left.function;
                    nodeMap.get(function).left = null;
                    nodeMap.get(function).right = null;
                    nodeMap.remove(temp);
                }
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
            System.out.println(" ".repeat(4 * level) + "-> " +"(" + root.variable + ")" + root.function);
            printTree(root.left, level + 1);
        }
    }
    public static int BDD_use(bdd tree, String input){
        node current = tree.root;
        int index = 0;
        while (current != null){
            if (input.charAt(index) == '0'){
                if (current.variable == tree.order.toCharArray()[index]) {
                    current = current.left;
                }
            }
            else if (input.charAt(index) == '1') {
                if (current.variable == tree.order.toCharArray()[index]) {
                    current = current.right;
                }
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
    public static void testSpravnosti(int numberOfVariables){
        for (int i = 0; i < 100; i++){
            String DNF = DNFgenerator.generateDNF(numberOfVariables);
            bdd tree = BDDcreate(DNF, getVariables.get(DNF));
            List<String> list = DNFgenerator.generate(numberOfVariables);
            for (String j : list){
                if (BDD_use(tree, j) != expressionEvaluator.evaluate(DNF, j)){
                    System.out.println("Error");
                }
            }
        }
    }
}