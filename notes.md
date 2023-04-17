# Getting Started Programming with Qt Widgets
- QApplication object manages application-wide resources and it necessary to run any Qt program that uses Qt Widgets.
For GUI applications that do not use Qt Widgets, you can use QGuiApplication instead.
- return a.exec(); makes the QApplication enter its event loop.
Examples of events are mouse presses and key strokes.
- Qt User Interface Compiler(uic)
reads the .ui file and creates a corresponding C++ header file, ui_notepad.h.
- <qt_installation_directory>\bin\qt-cmake -GNinja <source_directory>

# Qt for Beginners
- How a Qt program is compiled
    - 1. A .pro file is written to describe the project to compile
    - 2. A makefile is generated using qmake
    - 3. The program is built using make (or nmake or jom on windows)
- Qt class hierarchy
    - QObject 
    The most basic class
        - object name, a string
        - parenting system
        - signals and slots
        - event management
- Parenting system
    - When an object is destroyed, all of its children are destroyed as well.
    - All QObjects have findChild and findChildren methods that can be used to search for children of a given object.
    - Child widgets in a QWidget automatically appear inside the parent widget.
- The Meta Object
    - Introspection : capability of examining a type at run-time
    - Asynchronous function calls
    - Code produced by moc
        - signals and slots
        - methods that are used to retrieve meta-information from those marked class
        - properties handling
        - ...
- Important macros
    - Q_OBJECT 
    The moc is provided to translate the QT syntax like "connect", "signals", "slots", etc into regular C++ syntax.
    - slot signature and signal signature
- Creating custom signals and slots
    - add Q_OBJECT macro, require public inherit from QObject
    - add signals section, and write signals prototypes
    - add public slots or protected slots or private slots sections, and - write slots prototypes
    - implement slots as normal methods
    - establish connections
# Model/View Tutorial
- 在GUI中，表格、列表和树形小部件是常用的组件。这些小部件可以通过两种不同的方式访问数据。
    - 在GUI中，表格、列表和树形小部件是常用的组件。这些小部件可以通过两种不同的方式访问数据。
    - ModelView编程方式：小部件不维护内部数据容器，而是通过标准接口访问外部数据，避免了数据重复。
    这种方式一开始可能看起来比较复杂，但一旦您仔细学习，就会发现它不仅易于掌握，而且其众多优点也变得更加清晰。
- Qt提供的基本技术
    - 标准小部件和模型/视图小部件的区别
    - 表单和模型之间的适配器
    - 开发一个简单的模型/视图应用程序
    - 预定义的模型
    - 中级主题，例如
        - 树形界面
        - 选择
        - 委托
        - 使用模型测试
- 此外，您还将学习如何确定您的新应用程序是否可以使用模型/视图编程更轻松地编写，或者经典小部件同样适用。
本教程包含示例代码供您编辑和集成到您的项目中。教程的源代码位于Qt的examples/widgets/tutorials/modelview目录中。
如果需要更详细的信息，您可能还需要查阅参考文档。
- 1 Introduction
    - Model/View是一种技术，用于在处理数据集的小部件中将数据与视图分离。
    标准小部件并不是为了分离数据与视图而设计的，这就是为什么Qt有两种不同类型的小部件。
    两种类型的小部件看起来相同，但它们与数据的交互方式不同。
    - 1.1 Standard Widgets
        - 让我们更仔细地看一下标准表格小部件。
        表格小部件是一个二维数组，由用户可以更改的数据元素组成。
        通过读取和写入表格小部件提供的数据元素，可以将表格小部件集成到程序流程中。
        这种方法在许多应用程序中非常直观和有用，但使用标准表格小部件显示和编辑数据库表可能会出现问题。
        必须协调数据的两个副本：一个在小部件外部，一个在小部件内部。开发人员需要负责同步两个版本。
        此外，演示和数据之间的紧密耦合使得编写单元测试更加困难。
    - 1.2 Model/View to the Rescue
        - Model/view采用更灵活的架构提供了一个解决方案，消除了标准小部件可能出现的数据一致性问题。
        Model/view还使得使用相同数据的多个视图更容易，因为一个模型可以传递给多个视图。
        最重要的区别是，model/view小部件不在表格单元格后面存储数据。
        实际上，它们直接从您的数据中操作。
        由于视图类不知道您的数据结构，因此您需要提供一个包装器，使您的数据符合QAbstractItemModel接口。
        视图使用此接口从您的数据中读取和写入数据。
        实现QAbstractItemModel的类的任何实例都被称为模型。
        一旦视图接收到指向模型的指针，它就会读取和显示其内容，并成为其编辑器。
    - 1.3 Overview of the Model/View Widgets
        - Here is an of the model/view widgets and their corresponding standard widgets.
        - QListWidget QListView
        - QTableWidget QTableView
        - QTreeWidget QTreeView
        - QComboBox
    - 1.4 Using Adapters between Form and Models
        - 在表单和模型之间使用适配器非常方便。
        我们可以直接在表格中编辑存储在其中的数据，但是在文本字段中编辑数据更加方便。
        对于操作一个值（QLineEdit、QCheckBox等）而不是数据集的小部件，没有直接的模型/视图对应物，因此我们需要一个适配器来将表单连接到数据源。
        - QDataWidgetMapper是一个很好的解决方案，因为它将表单小部件映射到表行，并且非常容易为数据库表构建表单。
        - 另一个适配器的例子是QCompleter。
        Qt提供了QCompleter用于在Qt小部件（例如QComboBox和QLineEdit）中提供自动完成。
        QCompleter使用模型作为其数据源。
- 2 A Simple Model/View Application
    - 2.1 A Read Only Table
        - 如果你想开发一个模型/视图应用程序，你应该从哪里开始呢？
        我们建议从一个简单的示例开始，并逐步扩展它。这样可以更容易地理解架构。
        对于许多开发人员来说，在调用 IDE 之前详细了解模型/视图架构的复杂性已经被证明不是很方便。
        从一个简单的模型/视图应用程序开始，该应用程序具有演示数据，这样做起来更容易。不妨试试！只需将下面示例中的数据替换为您自己的数据即可。
        - 以下是7个非常简单且独立的应用程序，展示了模型/视图编程的不同方面。
        源代码可以在examples/widgets/tutorials/modelview目录中找到。
        - MyModel::rowCount()和MyModel::columnCount()方法提供了行和列的数量。
        当视图需要知道单元格的文本时，它会调用MyModel::data()方法。
        行和列信息由index参数指定，角色设置为Qt::DisplayRole。
        其他角色将在下一节中介绍。
        在我们的示例中，生成应显示的数据。在实际应用程序中，MyModel将拥有一个名为MyData的成员，它是所有读取和写入操作的目标。
        
        - 这个小例子展示了模型的被动性。
        模型并不知道何时会被使用或需要哪些数据，它只在每次视图请求数据时提供数据。
        当模型的数据需要更改时会发生什么呢？
        视图如何意识到数据已更改并需要重新读取？
        模型必须发出一个信号，指示已更改哪个单元格范围。这将在2.3节中进行演示。
    - 2.2 Extending the Read Only Example with Roles
        - 除了控制视图显示的文本之外，模型还控制文本的外观。当我们稍微更改模型时，我们会得到以下结果：
        - 实际上，只需要更改 data() 方法就可以设置字体、背景颜色、对齐方式和复选框。
        下面是产生上述结果的 data() 方法。
        区别在于，这次我们使用参数 int role 根据其值返回不同的信息。
        - 每个格式化属性都将通过调用data()方法单独请求模型。role参数用于让模型知道正在请求哪个属性：

        - 请参阅Qt名称空间文档以了解Qt :: ItemDataRole枚举的功能。
        - 现在我们需要确定使用分离的模型对应用程序的性能有何影响，因此让我们跟踪视图调用data()方法的频率。
        为了跟踪视图调用模型的次数，我们在data()方法中放置了一个调试语句，该语句记录在错误输出流上。
        在我们的小例子中，data()将被调用42次。每次将光标悬停在字段上时，data()将再次调用——每个单元格7次。
        {Qt6.3.2 实际测试，当光标悬停在某个cell的时候，只会请求ToolTipRole, 点击cell的时候会调用7次}
        - 这就是为什么重要的是确保当调用data()时数据可用且昂贵的查找操作已被缓存。
    - 2.3 A Clock inside a Table Cell
        - 我们仍然有一个只读表格，但这一次内容每秒钟改变一次，因为我们展示的是当前时间。
        在使时钟滴答的代码中缺少一些内容。我们需要每秒钟告诉视图时间已经改变，并且需要重新读取。我们可以使用一个定时器来实现这一点。在构造函数中，我们将其间隔设置为1秒，并连接其timeout信号。

        我们通过发出 dataChanged() 信号请求视图再次读取左上角单元格中的数据。请注意，我们没有显式连接 dataChanged() 信号到视图。这是在调用 setModel() 时自动发生的。
    - 2.4 Setting up Headers for Columns and Rows
        - 表头可以通过视图方法进行隐藏：tableView->verticalHeader()->hide();
        - 然而，标题内容是由Model设置的，因此我们需要重新实现headerData()方法：
        - 注意，headerData() 方法也有一个 role 参数，它与 MyModel::data() 中的 role 参数的含义相同。
        - 如果headerData没有根据传入的role返回正确类型，表头会直接不显示
    - 2.5 The Minimal Editing Example
        - 在这个示例中，我们将构建一个应用程序，通过重复输入到表格单元格中的值来自动填充窗口标题。为了能够轻松访问窗口标题，我们将QTableView放置在QMainWindow中。

        - 模型决定是否可用编辑功能。我们只需要修改模型，就可以启用可用的编辑功能。这是通过重新实现以下虚拟方法来完成的：setData()和flags()。

        - 我们使用二维数组QString m_gridData来存储数据。
        这使得m_gridData成为MyModel的核心。
        MyModel的其余部分充当包装器，将m_gridData适配到QAbstractItemModel接口。
        我们还引入了editCompleted()信号，使得可以将修改后的文本传递到窗口标题中。
        - 每次用户编辑单元格时，setData() 函数都会被调用。index 参数告诉我们哪个字段被编辑了，value 参数提供了编辑过程的结果。
        由于我们的单元格只包含文本，所以角色(role) 将始终被设置为 Qt::EditRole。
        如果存在复选框并且用户权限设置允许选择复选框，则调用也将使用 Qt::CheckStateRole 设置角色。
3 Intermediate Topics
