ListView.builder(
  itemCount: 100,
  itemBuilder: (BuildContext context, int index) {
    return ListTile(
      title: Text('Item $index'),
    );
  },
)