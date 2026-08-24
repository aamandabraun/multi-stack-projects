class SensorListener extends StatefulWidget {
  const SensorListener({super.key});

  @override
  State<SensorListener> createState() => _SensorListenerState();
}

class _SensorListenerState extends State<SensorListener> {
  late StreamSubscription _subscription;
  String _ultimoDado = 'Aguardando...';

  @override
  void initState() {
    super.initState();

    final stream = Stream.periodic(const Duration(seconds: 1), (i) => 'Leitura $i');

    _subscription = stream.listen((data) {
      setState(() {
        _ultimoDado = data;
      });
    });
  }

  @override
  void dispose() {
    _subscription.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Center(child: Text(_ultimoDado));
  }
}