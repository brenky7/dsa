package string;

import java.util.ArrayList;

public class SplitFunction {

    public static String[] split(String function, char variable) {
        String[] split = function.split("\\+");
        ArrayList<String> positive = new ArrayList<String>();
        ArrayList<String> negative = new ArrayList<String>();
        for (String i: split){
            if (i.contains("!" + variable)){
                i = i.replace("!" + variable, Character.toString('1'));
                negative.add(i);
            }
            else if (i.contains(Character.toString( variable))){
                i = i.replace(Character.toString(variable), Character.toString('1'));
                positive.add(i);
            }
            else {
                positive.add(i);
                negative.add(i);
            }
        }
        String positiv = String.join("+", positive);
        positiv = expressionModifier.modify(positiv);
        String negativ = String.join("+", negative);
        negativ = expressionModifier.modify(negativ);
        return new String[] {negativ, positiv};
    }
}
