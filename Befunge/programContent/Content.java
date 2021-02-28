package programContent;

import java.util.Arrays;
import java.util.Stack;

public class Content {
    public Content(int x, int y){
        stack = new Stack<>();
        direction = DIR.RIGHT;
        stringMode = false;
        bridge = false;
        field = new char[x * y];
        Arrays.fill(field, ' ');
    }
    public programContent.DIR direction;
    public Stack<Integer> stack;
    public boolean stringMode;
    public char inStack;
    public boolean bridge;
    public char[] field;
}