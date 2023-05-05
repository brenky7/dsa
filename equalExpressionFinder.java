package string;

import java.util.ArrayList;
import java.util.List;

public class equalExpressionFinder {
    public static String[] find(String left, String right){
        List leftList = new ArrayList<String>();
        List rightList = new ArrayList<String>();
        String[] leftSplit = left.split("\\+");
        String[] rightSplit = right.split("\\+");
        int equal = 0;
        for (String i: leftSplit){
            for (String j: rightSplit){
                if (i.equals(j)){
                    equal++;
                    break;
                }
            }
        }
        if (equal == leftSplit.length){
            return new String[] {left, left};
        }
        else{
            return new String[] {left, right};
        }
    }
}
