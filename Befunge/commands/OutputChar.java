package commands;

import programContent.Content;

public class OutputChar extends Command{
    @Override
    public void Action(Content content) {
        System.out.print((char)(int) content.stack.pop());
    }
}
