/*
 * Copyright 2019 Volker Berlin (i-net software)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import de.inetsoftware.jwebassembly.api.annotation.Export;
import de.inetsoftware.jwebassembly.web.dom.Document;
import de.inetsoftware.jwebassembly.web.dom.HTMLElement;
import de.inetsoftware.jwebassembly.web.dom.Text;
import de.inetsoftware.jwebassembly.web.dom.Window;

public class HelloWorld {

    @Export
    public static void main() {
        Document document = Window.document();
        HTMLElement div = document.createElement("div");
        Text text = document.createTextNode("Hello World, this text come from WebAssembly."); 
        div.appendChild( text );
        document.body().appendChild( div );
    }
}