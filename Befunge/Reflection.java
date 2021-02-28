import commands.Command;
import java.util.HashMap;
import programContent.Content;


public class Reflection {
    private static final HashMap<Character, String> commandName = new HashMap<>(){{
        put('>', "commands.TurnRight");
        put('v', "commands.TurnDown");
        put('<', "commands.TurnLeft");
        put('^', "commands.TurnUp");
        put('?', "commands.TurnRandom");
        put('+', "commands.Add");
        put('-', "commands.Subtraction");
        put('*', "commands.Multiplication");
        put('/', "commands.Divide");
        put('%', "commands.Modulo");
        put('!', "commands.Not");
        put('`', "commands.Greater");
        put('_', "commands.HorizontalIf");
        put('|', "commands.VerticalIf");
        put('\"', "commands.StringMode");
        put(':', "commands.Dup");
        put('\\', "commands.Swap");
        put('$', "commands.Pop");
        put('.', "commands.OutputInt");
        put(',', "commands.OutputChar");
        put('#', "commands.Bridge");
        put('g', "commands.Get");
        put('p', "commands.Put");
        put('&', "commands.InputInt");
        put('~', "commands.InputCharacter");
        put('@', "commands.End");
        put('i', "commands.InStack");

    }};
    private static final HashMap<Character, Command> commandObject= new HashMap<>();

    private static Command InputClass(Character className) throws Exception{
        java.lang.Class<?> cl = null;
        Command c = null;
        try {
            cl = java.lang.Class.forName(commandName.get(className));
            c = (Command) cl.newInstance();
        } catch (ClassNotFoundException e){
            System.err.println("Failed to load class: " + className);
        }
        return c;
    }

    public static void Act(Content program_content, char className) throws Exception {
        if (!commandObject.containsKey(className)) {
            //System.out.println(className);
            commandObject.put(className, InputClass(className));
        }
        commandObject.get(className).Action(program_content);
        //System.out.println(className);
    }

}