import 'package:flutter/material.dart';

class DetailsPage extends StatefulWidget {
  final Map prato;

  const DetailsPage({super.key, required this.prato});

  @override
  State<DetailsPage> createState() => _DetailsPageState();
}

class _DetailsPageState extends State<DetailsPage> {

  int quantidade = 1;

  @override
  Widget build(BuildContext context) {

    double total = quantidade * widget.prato["preco"];

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.prato["nome"]),
        backgroundColor: Colors.red,
      ),

      body: Container(
        padding: const EdgeInsets.all(20),

        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [

            Text(
              widget.prato["nome"],
              style: const TextStyle(
                fontSize: 28,
                fontWeight: FontWeight.bold,
              ),
            ),

            const SizedBox(height: 20),

            Text(widget.prato["descricao"]),

            const SizedBox(height: 20),

            Text(
              "Preço: R\$ ${widget.prato["preco"]}",
              style: const TextStyle(fontSize: 22),
            ),

            const SizedBox(height: 30),

            Row(
              children: [

                IconButton(
                  onPressed: () {
                    if (quantidade > 1) {
                      setState(() {
                        quantidade--;
                      });
                    }
                  },
                  icon: const Icon(Icons.remove_circle),
                ),

                Text(
                  quantidade.toString(),
                  style: const TextStyle(fontSize: 22),
                ),

                IconButton(
                  onPressed: () {
                    setState(() {
                      quantidade++;
                    });
                  },
                  icon: const Icon(Icons.add_circle),
                ),
              ],
            ),

            const SizedBox(height: 20),

            Text(
              "Total: R\$ ${total.toStringAsFixed(2)}",
              style: const TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold),
            ),

            const SizedBox(height: 40),

            ElevatedButton(
              onPressed: () {
                Navigator.pop(context);
              },
              child: const Text("Voltar"),
            ),
          ],
        ),
      ),
    );
  }
}