run the following command to create a teavm mvn project
```bash
mvn archetype:generate   -DarchetypeCatalog=local   -DarchetypeGroupId=org.teavm   -DarchetypeArtifactId=teavm-maven-webapp-wasm-gc   -DarchetypeVersion=0.11.0   -DgroupId=com.example   -DartifactId=my-wasm-app   -Dversion=1.0-SNAPSHOT   -DinteractiveMode=false
```

```bash
cd my-wasm-app/
mvn clean install
```

goto target/my-wasm-app-1.0-SNAPSHOT

```bash
cd target/my-wasm-app-1.0-SNAPSHOT/
```

find the index.html file

```bash
python3 -m http.server 8080
```

hit the url