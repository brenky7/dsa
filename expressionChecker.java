package string;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class expressionChecker {
    public static String check(String input){
        String pattern = "^![A-Z]\\+[A-Z]$";
        Pattern regex = Pattern.compile(pattern);
        Matcher matcher = regex.matcher(input);
        if (matcher.find()){
            return "1";
        }
        else {
            return input;
        }
    }
}
