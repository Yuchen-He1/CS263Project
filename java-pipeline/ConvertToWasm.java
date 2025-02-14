import de.inetsoftware.jwebassembly.JWebAssembly;
import java.io.File;
import java.io.IOException;

public class ConvertToWasm {
    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Usage: java ConvertToWasm <Java class file>");
            return;
        }

        String classFile = args[0];
        String wasmFile = classFile.replace(".class", ".wasm");

        System.out.println("Compiling " + classFile + " to WebAssembly...");
        
        JWebAssembly.compile(new File(classFile), new File(wasmFile));

        System.out.println("Compilation complete! Output: " + wasmFile);
    }
}
