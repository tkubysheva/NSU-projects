import java.util.HashMap;
import java.util.Map;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Properties;

/**
 * The Factory Class registers classes inherited from
 * class T and returns class objects by the key
 * from the properties file
 * @param <T> the class is the parent of those classes
 *           that need to be created
 */

public class Factory<T> {
    /**
     * A map that stories key-object pairs
     */
    private final Map<Character, T> commandObject= new HashMap<>();
    /**
     * A properties that stories key-className pairs
     */
    private final Properties commandName = new Properties();

    /**
     * A constructor that fills the properties commandName
     * @see Factory#commandName
     * @param propertiesName name of the properties file
     * @throws Exception if constructor can't read the file
     */
    Factory(String propertiesName) throws Exception{
        try (InputStream i = Factory.class.getResourceAsStream(propertiesName);
            BufferedReader r = new BufferedReader(new InputStreamReader(i))){
            commandName.load(r);
        } catch(Exception e) {
            throw new Exception(e.getMessage());
        }
    }

    /**
     * The function creates an object by the key
     * @param className object-key name
     * @return created class object
     * @throws Exception if file can't load
     */
    private T loadClass(char className) throws Exception{
        java.lang.Class<?> cl = null;
        T c = null;
        try {
            cl = java.lang.Class.forName(commandName.getProperty(Character.toString(className)));
            c = (T) cl.newInstance();
        } catch (Exception e){
            throw new Exception("Failed to load class: " + className);
        }
        return c;
    }

    /**
     * A public function that returns a class object by the key from the map
     * commandObject and if necessary creates the desired object
     * @param className object-key name
     * @return class object from the map commandObject
     * @throws Exception if file can't load
     */
    public T InputClass(char className) throws Exception{
        if (!commandObject.containsKey(className)) {
            commandObject.put(className, loadClass(className));
        }
        return commandObject.get(className);
    }
}