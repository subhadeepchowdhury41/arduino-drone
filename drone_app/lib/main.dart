import 'package:drone_app/notifier/drone_status_notifier.dart';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

void main() {
  runApp(const ProviderScope(
    child: MyApp())
  );
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Drone App',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const Dashboard(),
    );
  }
}

class Dashboard extends ConsumerStatefulWidget {
  const Dashboard({super.key});
  @override
  ConsumerState<ConsumerStatefulWidget> createState() => _DashboardState();
}

class _DashboardState extends ConsumerState<Dashboard> {
  final TextEditingController _ctrl = TextEditingController();
  @override
  void initState() {
    _ctrl.text = '192.168.126.66';
    super.initState();
  }
  @override
  Widget build(BuildContext context) {
    double height = MediaQuery.of(context).size.height;
    final statusNotifier = ref.watch(statusNotifierProvider);
    return Scaffold(
      body: Container(
        decoration: const BoxDecoration(
          gradient: LinearGradient(
            begin: Alignment.bottomCenter,
            end: Alignment.topCenter,
            colors: [Color.fromARGB(255, 3, 3, 3),
          Color.fromARGB(255, 8, 16, 22),
          Color.fromARGB(255, 7, 13, 20),
          ])
        ),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Expanded(
              flex: 2,
              child: Container(
                margin: const EdgeInsets.all(8),
                child: Row(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    Expanded(
                      flex: 4,
                      child: SizedBox(
                        height: height / 16,
                        child: TextFormField(
                          textAlignVertical: TextAlignVertical.center,
                          keyboardType: TextInputType.number,
                          controller: _ctrl,
                          decoration: InputDecoration(
                            enabledBorder: OutlineInputBorder(borderRadius: BorderRadius.circular(35),
                             gapPadding: 0,
                             borderSide: const BorderSide(
                              color: Color.fromARGB(255, 64, 73, 81), width: 3)),
                            focusedBorder: OutlineInputBorder(borderRadius: BorderRadius.circular(35),
                             gapPadding: 0,
                             borderSide: const BorderSide(
                              color: Color.fromARGB(255, 143, 174, 200), width: 3)),
                            fillColor: const Color.fromARGB(255, 252, 252, 252),
                            hintStyle: const TextStyle(fontWeight: FontWeight.w600,
                            color: Color.fromARGB(255, 95, 92, 92)
                            ),
                            hintText: 'Enter IP Address',
                            filled: true,
                            disabledBorder: OutlineInputBorder(borderRadius: BorderRadius.circular(35),
                             gapPadding: 0,
                             borderSide: const BorderSide(
                              color: Color.fromARGB(255, 45, 121, 184), width: 3)),
                            border: OutlineInputBorder(borderRadius: BorderRadius.circular(35),
                             gapPadding: 0,
                             borderSide: const BorderSide(
                              color: Colors.blue, width: 3))
                          ),
                        ),
                      ),
                    ),
                    Expanded(
                      flex: 2,
                      child: Padding(
                        padding: const EdgeInsets.all(13.0),
                        child: ElevatedButton(
                        style: ElevatedButton.styleFrom(
                          shape: RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(35),
                          ),
                          textStyle: const TextStyle(fontSize: 17, fontWeight: FontWeight.bold),
                          backgroundColor: Colors.blueAccent,
                          fixedSize: Size(double.infinity, height / 16),
                        ),
                        onPressed: () {
                          ref.read(statusNotifierProvider.notifier).setIp(_ctrl.text);
                        }, child: const Text('Set IP')),
                      ),
                    ),
                    
                  ],
                ),
              ),
            ),
            
            Expanded(
              flex: 5,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  Center(
                    child: Text(ref.read(statusNotifierProvider.notifier).ipConfirmed
                    ? (ref.read(statusNotifierProvider.notifier).ip) : 'IP not confirmed',
                    style: const TextStyle(color: Colors.white, fontSize: 19,
                    fontWeight: FontWeight.w500),
                    ),
                  ),
                  Padding(
                    padding: const EdgeInsets.symmetric(horizontal: 18.0),
                    child: ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        fixedSize: Size(double.infinity, height / 13),
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(35)
                        )
                      ),
                      child: ref.read(statusNotifierProvider.notifier).loading ?
                        const SizedBox(
                          height: 20,
                          width: 20,
                          child: CircularProgressIndicator(color: Colors.white, ))
                      : Text(
                        "Turn ${statusNotifier == 1 ? "Off" : "On"}",
                        style: const TextStyle(
                          fontSize: 19,
                          fontWeight: FontWeight.bold),
                      ),
                      onPressed: () {
                        ref.read(statusNotifierProvider.notifier).toggleStatus(
                          statusNotifier == null || statusNotifier == 0 ? 1 : 0
                        );
              },
            ),
                  ),
                  Text(ref.read(statusNotifierProvider.notifier)
                  .ipConfirmed.toString())
                ],
              ),
            ),
            
          ],
        ),
      ),
    );
  }
}