package string;

import java.util.ArrayList;
import java.util.List;

public class expressionModifier {

    public static String modify(String input){
        if (input.contains("+1+")){
            input = "1";
        }
        if (input.length() > 1 && ((input.charAt(0) == '1' && input.charAt(1) == '+') || (input.charAt(input.length() - 1) == '1' && input.charAt(input.length() - 2) == '+'))){
            input = "1";
        }
        else {
            if (input.length() > 1 && input.contains("1")) {
                input = input.replace("1", "");
            }
        }
        if (input.equals("")){
            input = "0";
        }
        while (input.length() > 1){
            if (input.contains("11")){
                input = input.replace("11", "1");
            }
            else {
                break;
            }
        }
        List<String> list = new ArrayList<String>();
        String[] split = input.split("\\+");
        for (String i: split){
            if (!list.contains(i)){
                list.add(i);
            }
        }
        input = String.join("+", list);
        if (input.length() < 5){
            input = expressionChecker.check(input);
        }
        return input;
    }
}
