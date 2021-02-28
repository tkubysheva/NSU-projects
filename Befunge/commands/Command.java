package commands;
import java.util.Stack;
import programContent.Content;

public abstract class Command {
    protected int pop(Stack<Integer> s){
        if(!s.empty()){
            return s.pop();
        }
        return 0;
    }
    public abstract void Action(Content content);
}
